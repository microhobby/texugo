<?php

/**
 * Data From Get
 * Parse data from get and set in fields
 */
abstract class DataFromGet
{
	private $reflection;

	function __construct() 
	{
		$this->reflection = new ReflectionClass($this);
		$fields = $this->reflection->
				getProperties(ReflectionProperty::IS_PUBLIC);
		
		foreach ($fields as $field)
		{
			$this->{$field->getName()} = $_GET[$field->getName()];
		}
	}

	public function saveJson()
	{
		$data = json_encode($this, JSON_PRETTY_PRINT);
		file_put_contents(get_class($this).".json", $data);
	}
}