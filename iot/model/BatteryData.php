<?php

require_once "DataFromGet.php";

/**
 * Battery Data
 */
class BatteryData extends DataFromGet
{
          public $SOC = 0;
          public $Volt = 0;
          
          function __construct()
          {
		DataFromGet::__construct();
          }
}

?>