# -*- coding: UTF-8 -*-

import os
import sys
import time
import tempfile
import urllib2
import json
import contextlib
import zipfile

from global_var import version,company_id

class update_client(object):
    mydir = os.path.dirname(os.path.realpath(__file__))
    
    def __init__(self):
        is_64bit = (sys.maxsize > 2**32)
        if 'win32' == sys.platform:
            platform = "win32"
        elif 'linux2' == sys.platform:
            if is_64bit:
                platform = "linux64"
            else:
                platform = "linux32"
        else:
            print "not support platform"
            return None
        ver = version.replace(".", "/");
        self.query_url = "http://www.example.com/test/"+str(company_id)+"/"+platform+"/"+ver

    def upgrade(self):
        if False == self.need_upgrade():
            return True
        self.update_myself()

    def need_upgrade(self):
        resource = urllib2.urlopen(self.query_url)
        resp = resource.read()
        result = json.loads(resp)
        if 1 == result["upgrade"]:
            self.update_url = urllib2.unquote(result["url"]).decode('utf8')
            return True
        else:
            return False
    
    def download_file(self, url):
        baseFile = os.path.basename(url)
        
        os.umask(0002)
        temp_path = tempfile.gettempdir()
        try:
            file = os.path.join(temp_path,baseFile)
            
            req = urllib2.urlopen(url)
            total_size = int(req.info().getheader('Content-Length').strip())
            downloaded = 0
            CHUNK = 256 * 10240
            with open(file, 'wb') as fp:
                while True:
                    chunk = req.read(CHUNK)
                    downloaded += len(chunk)
                    if not chunk: break
                    fp.write(chunk)
        except urllib2.HTTPError, e:
            print "HTTP Error:",e.code , url
            return False
        except urllib2.URLError, e:
            print "URL Error:",e.reason , url
            return False
        
        return file

    def unzip(self, source, target):
        with contextlib.closing(zipfile.ZipFile(source , "r")) as z:
            z.extractall(target)

    def restart_myself(self):
        executable = sys.executable
        args = sys.argv[:]
        args.insert(0, sys.executable)
        time.sleep(2)
        os.execvp(executable, args)

    def update_myself(self):
        file = self.download_file(self.update_url)
        if file == False:
            print "update Failed. download error"
            return False
        self.unzip(file, self.mydir)
        self.restart_myself()

#test
def main():
    instance = update_client()
    ret = instance.upgrade()

if __name__ == '__main__':
    main()
