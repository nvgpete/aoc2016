#!/usr/bin/php
<?php
  $todo=[['txt' => 'mmsxrhfx','x' => 0,'y'=>0 ]];
  $prt=1;
  $max=0;
  while (count($todo)) {
    $a=array_shift($todo);
    if ($a['x']==3 && $a['y']==3) {
      if ($prt)  { 
        echo 'Path='.substr($a['txt'],8)."\n";
        $prt=0; 
      } else if (strlen($a['txt'])>$max) $max=strlen($a['txt']);
      continue;
    }  
    $h=md5($a['txt']);
    if ($a['y'] && $h[0]>'a') {
      $b=$a;
      $b['txt'].='U';
      $b['y']--;
      $todo[]=$b;
    }  
    if ($a['y']<3 && $h[1]>'a') {
      $b=$a;
      $b['txt'].='D';
      $b['y']++;
      $todo[]=$b;
    }
    if ($a['x'] && $h[2]>'a') {
      $b=$a;
      $b['txt'].='L';
      $b['x']--;
      $todo[]=$b;
    }  
    if ($a['x']<3 && $h[3]>'a') {
      $b=$a;
      $b['txt'].='R';
      $b['x']++;
      $todo[]=$b;
    }  
  } 
  $max-=8;
  echo "Longest Path=$max\n";
?>