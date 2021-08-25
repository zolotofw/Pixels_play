#include "libjpeg-wrapper.hpp"

using namespace std;


const char *libjpeg_failed_to_open_file::what() const noexcept
{
	return "failed to open file";
}


const char *libjpeg_failed_to_save_file::what() const noexcept
{
	return "failed to save file";
}


libjpeg_wrapper::libjpeg_wrapper(const char *path)
{
	_file = fopen(path, "r+b");
	if (_file == nullptr)
	{
		throw libjpeg_failed_to_open_file {};
	}

	_decompress_error.error_exit = [](j_common_ptr){};
	_decompress_info.err = jpeg_std_error(&_decompress_error);
	jpeg_create_decompress(&_decompress_info);
	jpeg_stdio_src(&_decompress_info, _file);

	jpeg_read_header(&_decompress_info, TRUE);
	_coefficients = jpeg_read_coefficients(&_decompress_info);

	jpeg_component_info *red_channel = _decompress_info.comp_info;
	jpeg_component_info *green_channel = _decompress_info.comp_info + 1;
	jpeg_component_info *blue_channel = _decompress_info.comp_info + 2;

	_values_in_components[0] = red_channel->width_in_blocks * red_channel->height_in_blocks;
	_values_in_components[1] = green_channel->width_in_blocks * green_channel->height_in_blocks;
	_values_in_components[2] = blue_channel->width_in_blocks * blue_channel->height_in_blocks;
	_values_in_row[0] = red_channel->width_in_blocks;
	_values_in_row[1] = green_channel->width_in_blocks;
	_values_in_row[2] = blue_channel->width_in_blocks;

	_capacity = (_values_in_components[0] + _values_in_components[1] + _values_in_components[2]) / 8;
}


libjpeg_wrapper::~libjpeg_wrapper()
{
	jpeg_finish_decompress(&_decompress_info);
	fclose(_file);
}


size_t libjpeg_wrapper::capacity() const
{
	return _capacity;
}


JCOEF &libjpeg_wrapper::get_coefficient_at(size_t index)
{
	size_t component {0};
	for ( ; index >= _values_in_components[component] && component < 3; ++component)
	{
		index -= _values_in_components[component];
	}

	size_t row {static_cast<size_t>(index / _values_in_row[component])};
	size_t column {static_cast<size_t>(index - row * _values_in_row[component])};
	JBLOCKARRAY block {(_decompress_info.mem->access_virt_barray)(reinterpret_cast<j_common_ptr>(&_decompress_info), _coefficients[component], row, static_cast<JDIMENSION>(1), TRUE)};
	JCOEFPTR coefficient_pointer {block[0][column]};

	return coefficient_pointer[0];
}


void libjpeg_wrapper::save(const char *path)
{
	FILE *destination_file = fopen(path, "wb");
	if (!destination_file)
	{
		throw libjpeg_failed_to_save_file {};
	}

	jpeg_compress_struct compress_info;
	jpeg_error_mgr compress_error;

	compress_info.err = jpeg_std_error(&compress_error);
	jpeg_create_compress(&compress_info);
	jpeg_stdio_dest(&compress_info, destination_file);

	jpeg_copy_critical_parameters(&_decompress_info, &compress_info);

	jpeg_write_coefficients(&compress_info, _coefficients);

	jpeg_finish_compress(&compress_info);
	fclose(destination_file);
}

