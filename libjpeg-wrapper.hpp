#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include "libjpeg/jpeglib.h"


class libjpeg_exception
	:
	public std::exception
{
};


class libjpeg_failed_to_open_file
	:
	public libjpeg_exception
{
public:
	const char *what() const noexcept override;
};


class libjpeg_failed_to_save_file
	:
	public libjpeg_exception
{
public:
	const char *what() const noexcept override;
};


class libjpeg_wrapper
{
public:
	libjpeg_wrapper(const char *path);
	~libjpeg_wrapper();

	std::size_t capacity() const;
	JCOEF &get_coefficient_at(std::size_t index);

	void save(const char *path);

private:
	std::FILE *_file;
	jpeg_decompress_struct _decompress_info;
	jpeg_error_mgr _decompress_error;
	jvirt_barray_ptr *_coefficients;

	int _values_in_components[3];
	int _values_in_row[3];

	std::size_t _capacity;
};

