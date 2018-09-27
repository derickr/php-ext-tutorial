--TEST--
polar_to_cartesian() #1
--FILE--
<?php
var_dump(polar_to_cartesian(1, 0));
var_dump(polar_to_cartesian(1, 90));
var_dump(polar_to_cartesian(0.7071067811865475244, 45));
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
  float(6.1232339957368E-17)
  [1]=>
  float(1)
}
array(2) {
  [0]=>
  float(0.5)
  [1]=>
  float(0.5)
}
