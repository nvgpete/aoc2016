#! /usr/bin/php
<?php
  $list=[];
  for ($i=1; $i<=5; $i++) $list[]=$i;
  while (count($list)>1) {
    unset($list[count($list)/2]);
    $list[]=$list[0];
    array_splice($list,0,1);
  }
  echo $list[0]."\n";
?>