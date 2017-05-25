#!/usr/bin/python3
# -*- coding: utf-8 -*-

from datetime import datetime
import os
import sqlite3
import subprocess
import sys
import json
import chardet

def bytes_to_u8s(b=b''):
	encodings = ['utf-8', 'gbk', 'big5', None]
	onerror = 'strict'
	s=''
	for encoding in encodings:
		if not encodings:
			encoding = chardet.detect(b)['encoding']
			onerror='ignore'

		try:
			s = b.decode(encoding, errors=onerror)
			break
		except UnicodeDecodeError:
			continue
	return s

class MyInxdb(object):
	tblname = "t_index_0"

	def __init__(self, dbpath):
		super().__init__()
		self.__init_database(dbpath)

	def __fts5_pragma_check(self):
		with sqlite3.connect(':memory:') as conn:
			cur = conn.cursor()
			cur.execute('pragma compile_options;')
			available_pragmas = cur.fetchall()

		if ('ENABLE_FTS5',) in available_pragmas:
			return True
		else:
			return False

	def __init_database(self, dbpath):
		if os.path.exists(dbpath):
			self.__conn = sqlite3.connect(dbpath, check_same_thread=False)
			return

		self.__conn = sqlite3.connect(dbpath, check_same_thread=False)
		cur = self.__conn.cursor()

		if self.__fts5_pragma_check():
			cur.execute('''CREATE VIRTUAL TABLE IF NOT EXISTS ''' + self.tblname + ''' USING fts5(
						   path,
						   filetype,
						   fmod,
						   filesize,
						   ctime,
						   mtime,
						   atime,
						   uid,
						   gid,
					   )''')

			cur.execute('''PRAGMA user_version = 2;''')

		else:
			cur.execute('''CREATE VIRTUAL TABLE IF NOT EXISTS ''' + self.tblname + ''' USING fts4(
						   path,
						   filetype,
						   fmod,
						   filesize,
						   ctime,
						   mtime,
						   atime,
						   uid,
						   gid,
					   )''')
			cur.execute('''PRAGMA user_version = 1;''')
		cur.close()
		self.__conn.commit()

	def insert_record(self, table): 
		cur = self.__conn.cursor()
		for x in table:
			cur.execute( '''INSERT INTO ''' + self.tblname + ''' VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)''', (x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]))
		cur.close()
		self.__conn.commit()

	def get_records_contain_path(self, path, limit=20, offset=0):
		cur = self.__conn.cursor()
		cur.execute('''SELECT * FROM ''' + self.tblname + ''' where ''' + self.tblname + ''' MATCH \'{}\' LIMIT {} OFFSET {}'''.format(path, limit, offset))
		result = cur.fetchall()
		cur.execute('''SELECT count(*) FROM ''' + self.tblname + ''' where ''' + self.tblname + ''' MATCH \'{}\' '''.format(path))
		count = cur.fetchall()
		cur.close()
		return (count, result)

	def close(self):
		self.__conn.close()
	
import scandir
#  MORE GLOBAL VARIABLES
EXCLUDE = [b'proc', b'my_index', b'var']

def crawling_drives(root_dir, version, dbpath):
	def error(err):
		print(err)

	global EXCLUDE

	table = []
	dir_list = []
	file_list = []
	root_dir = root_dir.rstrip('/') if root_dir!='/' else '/'
	rootlen = len(root_dir) if root_dir!='/' else 0

	tbl_path = os.path.join(dbpath, "t_index_{}").format(version) + ".db"
	indexdb = MyInxdb(tbl_path) 

	if not os.path.exists(root_dir):
		error(root_dir + " not exists!!!")
		return False

	root_stats = os.lstat(root_dir)
	if os.path.ismount(root_dir):
		mountpoint=True
		rootpath = '/'
		filetype = 1
		fmod = root_stats.st_mode
		filesize = 0
		ctime = root_stats.st_ctime.__trunc__()
		mtime = root_stats.st_mtime.__trunc__()
		atime = root_stats.st_atime.__trunc__()
		uid = root_stats.st_uid
		gid = root_stats.st_gid
	elif os.path.isdir(root_dir):
		rootpath = root_dir
		filetype = 1
		fmod = root_stats.st_mode
		filesize = 0
		ctime = root_stats.st_ctime.__trunc__()
		mtime = root_stats.st_mtime.__trunc__()
		atime = root_stats.st_atime.__trunc__()
		uid = root_stats.st_uid
		gid = root_stats.st_gid
	else:
		error( root_dir + " is not a mount path or directory")
		return 

	root = (rootpath, filetype, fmod, filesize, ctime, mtime, atime, uid, gid)
	dir_list.append(root)

	for parent, dirs, files in scandir.walk(bytes(root_dir, encoding='utf-8'), onerror=error):
		dirs.sort()
		files.sort()
		dirs[:] = [d for d in dirs if d not in EXCLUDE]

		for dname in dirs:
			path = os.path.join(parent, dname)
			utf_path = bytes_to_u8s(path)
			filetype = 1
			try:
				stats = os.lstat(path)
				ctime = stats.st_ctime.__trunc__()
				mtime = stats.st_mtime.__trunc__()
				atime = stats.st_atime.__trunc__()
				fmod = stats.st_mode
				uid = stats.st_uid
				gid = stats.st_gid
				size = 0
			except:
				print('Cant access: ' + str(path))
				return False
			if mountpoint:
				child_dir = (utf_path[rootlen:], filetype, fmod, size, ctime, mtime, atime, uid, gid)
			else:
				child_dir = (utf_path, filetype, fmod, size, ctime, mtime, atime, uid, gid, version, ancestor)
			dir_list.append(child_dir)

		for fname in files:
			path = os.path.join(parent, fname)
			utf_path = bytes_to_u8s(path)
			filetype = 0
			try:
				stats = os.lstat(path)
				ctime = stats.st_ctime.__trunc__()
				mtime = stats.st_mtime.__trunc__()
				atime = stats.st_atime.__trunc__()
				fmod = stats.st_mode
				uid = stats.st_uid
				gid = stats.st_gid
				size = stats.st_size
			except:
				print('Cant access: ' + str(path))
				size = 0
			if mountpoint:
				child_file = (utf_path[rootlen:], filetype, fmod, size, ctime, mtime, atime, uid, gid)
			else:
				child_file = (utf_path, filetype, fmod, size, ctime, mtime, atime, uid, gid)
			file_list.append(child_file)

	table = dir_list + file_list
	indexdb.insert_record(table)
	indexdb.close()

def query_like_path_pretty(keyword, version, dbpath, limit=20, offset=0):
	try:
		keyword = match_query_adjustment(keyword)
		tbl_path = os.path.join(dbpath, "t_index_{}").format(version) + ".db"
		indexdb = MyInxdb(tbl_path) 
		
		key=["path", "filetype", "fmod", "filesize", "ctime", "mtime", "atime", "uid", "gid"]
		result = indexdb.get_records_contain_path(keyword, limit, offset)
		indexdb.close()
		ret = {}
		ret['count'] = result[0][0][0]
		ret['data'] = [dict(zip(key,row)) for row in result[1]]
		ret['code'] = 0
		return json.dumps(ret)
	except :
		ret = {}
		ret['code']=1
		ret['msg'] =str(sys.exc_info()[1])
		return json.dumps(ret)

def match_query_adjustment(input):
	if '?' in input or '\\' in input:
		for x in ['\\', '?']:
			input = input.replace(x, '')

	query_words = input.strip().split()
	words_quoted = []

	def fts5_pragma_check():
		with sqlite3.connect(':memory:') as conn:
			cur = conn.cursor()
			cur.execute('pragma compile_options;')
			available_pragmas = cur.fetchall()

		if ('ENABLE_FTS5',) in available_pragmas:
			return True
		else:
			return False

	FTS5_AVAILABLE=fts5_pragma_check()

	if FTS5_AVAILABLE:
		# MINUS SIGN MARKS PHRASES THAT MUST NOT APPEAR IN RESULTS
		words_no_minus = []
		excluded_words = []
		for x in query_words:
			if x.startswith('-'):
				if len(x) > 1:
					excluded_words.append(x[1:])
			else:
				words_no_minus.append(x)

		if not words_no_minus:
			words_no_minus.append('1')

		# QUOTED PHRASES ARE SEARCHED WITHOUT WILD CARD * AT THE END
		final_query = ''
		for x in words_no_minus:
			if '\"' in x:
				if x.startswith('\"') and x.endswith('\"'):
					x = x.replace('\"', '')
					final_query += '"{}" '.format(x)
					words_quoted.append(x)
					continue
				x = x.replace('\"', '')
			if '\'' in x:
				if x.startswith('\'') and x.endswith('\''):
					x = x.replace('\'', '')
					final_query += '"{}" '.format(x)
					words_quoted.append(x)
					continue
				x = x.replace('\'', '')
			final_query += '"{}"* '.format(x)

		if len(excluded_words) > 0:
			exclude_query_part = ''
			for x in excluded_words:
				x_is_quoted = False
				if '\"' in x:
					if x.startswith('\"') and x.endswith('\"'):
						x_is_quoted = True
					x = x.replace('\"', '')
				if '\'' in x:
					if x.startswith('\'') and x.endswith('\''):
						x_is_quoted = True
					x = x.replace('\'', '')
				if x_is_quoted:
					if len(x) > 1:
						exclude_query_part += 'NOT {} '.format(x)
				else:
					exclude_query_part += 'NOT {}* '.format(x)

			final_query = '{} {}'.format(final_query, exclude_query_part)

		return final_query

	if not FTS5_AVAILABLE:
		final_query = ''
		words_quoted = []
		for x in query_words:
			if '\"' in x:
				if x.startswith('\"') and x.endswith('\"'):
					x = x.replace('\"', '')
					final_query += '"{}" '.format(x)
					words_quoted.append(x)
					continue
				x = x.replace('\"', '')
			if '\'' in x:
				if x.startswith('\'') and x.endswith('\''):
					x = x.replace('\'', '')
					final_query += '"{}" '.format(x)
					words_quoted.append(x)
					continue
				x = x.replace('\'', '')

			final_query += '{}* '.format(x)

		return final_query


if __name__ == '__main__':
#	crawling_drives(sys.argv[1], int(sys.argv[2]), sys.argv[3])
#	ret = query_like_path_pretty(sys.argv[1], int(sys.argv[2]), sys.argv[3])
	ret = query_like_path_pretty("/usr/share", int(sys.argv[2]), sys.argv[3])
	print(ret)

