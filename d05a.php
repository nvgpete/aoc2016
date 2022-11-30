#!/usr/bin/php
<?php
  $n=1;
  $p='';
  $p2='xxxxxxxx';
  do {
    while (strncmp(md5('reyedfim'.$n),'00000',5)) $n++;
    $h=md5('reyedfim'.$n);
    $c=$h[5];
    if (strlen($p)<8) $p.=$h[5];
    if ($c<'8' && $p2[$c&7]=='x') $p2[$c&7]=$h[6];
    $n++;
  } while (strpos($p2,'x')!==false);
  echo "passwd1=$p\n";
  echo "passwd2=$p2\n";  
?>