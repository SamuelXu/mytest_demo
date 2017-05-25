<?php

date_default_timezone_set('Asia/Shanghai');
declare(ticks = 1);
set_time_limit(0);

error_reporting(E_ALL|E_STRICT);
ini_set("display_errors","on");

define('MONGO_HOST', "127.0.0.1");
define('MONGO_PORT', 27017);
define('MONGO_CLIENT_PATH', 'test1');

function mongo_get_conn()
{
    $conn = new MongoClient( "mongodb://". MONGO_HOST . ":" . MONGO_PORT);

    return $conn;
}

function any_encoding_to_utf8( &$text )
{
    $text = iconv(mb_detect_encoding($text, mb_detect_order(), true), "UTF-8", $text);
}

function convert_to_unix($path)
{
    if ($path[0] == '/' || stripos($path, ":\\") != 1) {
        return $path;
    }
    $path = str_replace(':\\', '/', $path);
    $path = preg_replace('/\/+/', '/', $path);
    return $path;
}

function mongo_update_insert($task_id, $history_id, $path)
{
    $col_name = "id" . $task_id;

    $fpath = trim(str_replace( '//', '/', $path), '/');
    any_encoding_to_utf8( $fpath);
    $path_array = explode('/', $fpath );
    $path_num = count( $path_array );

    $conn = mongo_get_conn();
    $col = $conn->selectCollection( MONGO_CLIENT_PATH, $col_name);
    
    foreach( $path_array as $i => $child_path ) {
        $parent = array_slice($path_array, 0, $i);

//update( { "path":"bb", "type":"d", "parent":["cc"]}, { $addToSet: {"update":1}}, {upsert:true})
	$query = array('path'=>$child_path, 'parent'=>$parent, 'type'=>"d");
    if ( $i == $path_num - 1 ) {
        $query["type"] = "f";
    }
	$data = array('$addToSet'=> array("update" => $history_id));
	$upsert = array('upsert'=>true);
        $col->update($query, $data, $upsert);
    }

    $conn->close();
}

function mongo_list_path($task_id, $path, $history_id)
{
    $col_name = "id" . $task_id;
    $result = array();

    if (empty($path) ) {
	    $path_array = array();
    } else {
        $path = convert_to_unix($path);
        $fpath = trim(str_replace( '//', '/', $path), '/');
	    any_encoding_to_utf8( $fpath);
	    if(empty($fpath)) {
		    $path_array = array();
	    } else {
		    $path_array = explode('/', $fpath );
	    }
    }

    $conn = mongo_get_conn();
    $col = $conn->selectCollection( MONGO_CLIENT_PATH, $col_name);

    //    find( {"parent":["Books", "Programming"], "update":5} )
    $doc['parent'] = $path_array;
    if($history_id != 0 ) {
        $doc['update'] = $history_id;
    }

    $cursor = $col->find($doc);
    foreach( $cursor as $ret ) {
        $result[] = array("path"=>$ret["path"], "type"=>$ret["type"]);
    }

    $conn->close();

    return $result;
}

function mongo_search($task_id, $path, $type=NULL)
{
    $col_name = "id" . $task_id;
    $result = array();

    if(empty($path)) {
        return array();
    }

    $path = convert_to_unix($path);
    $fpath = trim(str_replace( '//', '/', $path), '/');
    any_encoding_to_utf8( $fpath);

    $conn = mongo_get_conn();
    $col = $conn->selectCollection( MONGO_CLIENT_PATH, $col_name);

    $doc = array( 'path' => $fpath);
    if( !empty($type)) {
        $doc['type'] = $type;
    }

    $cursor = $col->find($doc);
    foreach( $cursor as $ret ) {
        $result[] = implode("/", $ret["parent"]) . '/' . $ret["path"];
    }

    $conn->close();

    return $result;
}

$a = array (
		"/home/samuel/test_paths/ee/install.sh",
		"/home/samuel/test_paths/redis.tgz",
		"/home/samuel/test_paths/xor_speed_test.php",
		"/home/samuel/test_paths/test.sh",
		"/home/samuel/test_paths/aa/bb/cc/redis_pop.php",
		"/home/samuel/test_paths/aa/bb/redis_push.php",
		"/home/samuel/test_paths/aa/bb/test.sh",
		"/home/samuel/test_paths/aa/files.zip",
	   );

$taskid=12345;
$history_id=3;

//foreach($a as $path) {
//	mongo_update_insert( $taskid, $history_id, $path);
//}

//array(6) {
//    [0]=>
//        array(2) {
//            ["path"]=>
//                string(2) "ee"
//            ["type"]=>
//                string(1) "d"
//        }
//    [1]=>
//        array(2) {
//            ["path"]=>
//                string(2) "dd"
//            ["type"]=>
//                string(1) "d"
//        }
//    [2]=>
//        array(2) {
//            ["path"]=>
//                string(9) "redis.tgz"
//            ["type"]=>
//                string(1) "f"
//        }
//    [3]=>
//        array(2) {
//            ["path"]=>
//                string(18) "xor_speed_test.php"
//            ["type"]=>
//                string(1) "f"
//        }
//    [4]=>
//        array(2) {
//            ["path"]=>
//                string(7) "test.sh"
//            ["type"]=>
//                string(1) "f"
//        }
//    [5]=>
//        array(2) {
//            ["path"]=>
//                string(2) "aa"
//            ["type"]=>
//                string(1) "d"
//        }
//}
$p = "/home/samuel/test_paths";
$path1 = mongo_list_path($taskid, $p, $history_id);
if(empty($path1)) {
    echo "null path\n";
    return null;
}
var_dump($path1);

//array(2) {
//    [0]=>
//        string(30) "home/samuel/test_paths/test.sh"
//        [1]=>
//        string(36) "home/samuel/test_paths/aa/bb/test.sh"
//}
$path_1 = mongo_search($taskid, "test.sh", "f");
var_dump($path_1);

