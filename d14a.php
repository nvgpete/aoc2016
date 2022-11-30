#!/usr/bin/php
<?php
  $n=0;
  $cnt=0;
  $pad=[];
  $ff=[];
  $last=0;
  do {
    $s=md5('ahsbgdzn'.$n);
//    for ($i=0; $i<2016; $i++) $s=md5($s);
    if (preg_match("/(.)\\1\\1\\1\\1/",$s,$mm)) {
      foreach ($ff as $kk => $cc) {
        if ($n-$kk>1000) unset($ff[$kk]);
        else if (strpos($cc,$mm[0][0])) {
          $pad[]=$kk;
          if (count($pad)==64) $last=$kk+1000;
          unset($ff[$kk]);
        }  
      }
      sort($pad);
    }
    if (preg_match("/(.)\\1\\1/",$s,$mm)) {
      $ff[$n]=' ';  
      foreach ($mm as $ss) $ff[$n].=$ss[0];
    }  
    $n++;
  } while (count($pad)<64 && $last<$n);
  echo "pad 64=$pad[63]\n"; 
?>