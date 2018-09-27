--TEST--
cartesian_to_polar() #1
--FILE--
<?php
var_dump(cartesian_to_polar(1, 0));
var_dump(cartesian_to_polar(0, 1));
var_dump(cartesian_to_polar(0.5, 0.5));
?>
--EXPECT--
array(2) {
  [0]=>
  float(1)
  [1]=>
  float(0)
}
array(2) {
  [0]=>
  float(1)
  [1]=>
  float(90)
}
array(2) {
  [0]=>
  float(0.70710678118655)
  [1]=>
  float(45)
}
