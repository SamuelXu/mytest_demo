<?php
error_reporting(E_ALL|E_STRICT);
ini_set("display_errors","on");

// 连接
$m = new Mongo("192.168.8.100:65431");

// 选择数据库
$db = $m->myTest;
$collection = $db->test;

// 添加记录
$obj = array("title" => "第一个","detail" => "测试");
$collection->insert($obj);

$obj = array("title" => "第二个","online" => true);
$collection->insert($obj);

// 查询
$cursor = $collection->find();
foreach($cursor as $obj)
{
	//var_dump($obj);
	print $obj['title']."\n";
}

// 条件查询
$connection = array("online" => true);
$cursor = $collection->find($connection);
foreach($cursor as $obj)
{
	//var_dump($obj);
	print $obj['title']."\n";
}

// 删除记录
//$del = array("online" => true);
//$collection->remove($del);

// 更新记录
$oldobj = array("title" => "第二个","online" => true);
$newobj = array("title" => "第二个","online" => false);
$collection->update($oldobj,$newobj);

// 删除库
//$m->dropDB("myTest");

// 关闭连接
$m->close();

