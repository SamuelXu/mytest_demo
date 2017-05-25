<?php
require_once( "forceutf8-master/src/ForceUTF8/Encoding.php");

error_reporting(E_ALL); 

function any_encoding_to_utf8( &$text )
{
    if ( strcasecmp('UTF-8', mb_detect_encoding($text, 'UTF-8', true)) == 0) {
        return true;
    }
//    $text = mb_convert_encoding($text, "UTF-8");
    $result = iconv("gbk", "utf-8", $text);
    if ( strcasecmp('UTF-8', mb_detect_encoding($result, 'UTF-8', true)) == 0) {
        $text = $result;
        return true;
    }
//    if ( $result === FALSE) {
//        $text = \ForceUTF8\Encoding::toUTF8($text);
//    } else {
//        $text = $result;
//    }
}

$str = file_get_contents("mixed_encodings");

any_encoding_to_utf8($str);

print $str . "\n";
