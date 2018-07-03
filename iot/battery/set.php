<?php

require_once "../model/BatteryData.php";

$batData = new BatteryData();
$batData->saveJson();
