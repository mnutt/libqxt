#!/usr/bin/php-cgi
<?php
if(empty($_SERVER['PATH_INFO']) || $_SERVER['PATH_INFO'] == '/') {
    $_SERVER['PATH_INFO'] = "/index.php";
} elseif($_SERVER["PATH_INFO"][0] != '/') {
    $_SERVER["PATH_INFO"] = '/'.$_SERVER["PATH_INFO"];
}
chdir(dirname("/var/www/html$_SERVER[PATH_INFO]"));
if(strstr($_SERVER['PATH_INFO'], ".php")) {
    include_once("/var/www/html$_SERVER[PATH_INFO]");
} else {
    if(strstr($_SERVER['PATH_INFO'], ".css")) {
        header("Content-type: text/css");
    }
    readfile("/var/www/html$_SERVER[PATH_INFO]");
}

?>
