#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

#include "php_geospatial.h"
#include "geo_array.h"
#include "algorithms.h"

static int parse_point_pair(zval *coordinates, double *lon, double *lat)
{
	HashTable *coords;
	zval *z_lon, *z_lat;

	if (Z_TYPE_P(coordinates) != IS_ARRAY) {
		zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0 TSRMLS_CC, "Expected a coordinate pair as an array, but %s given", zend_zval_type_name(coordinates));
		return 0;
	}

	coords = HASH_OF(coordinates);
	if (coords->nNumOfElements != 2) {
		return 0;
	}

	if ((z_lon = zend_hash_index_find(coords, 0)) == NULL) {
		return 0;
	}
	if ((z_lat = zend_hash_index_find(coords, 1)) == NULL) {
		return 0;
	}
	convert_to_double_ex(z_lon);
	convert_to_double_ex(z_lat);
	*lon = Z_DVAL_P(z_lon);
	*lat = Z_DVAL_P(z_lat);

	return 1;
}


geo_array *geo_hashtable_to_array(zval *array)
{
	geo_array *tmp;
	int element_count, i = 0;
	zval *entry;
	double lon, lat;

	element_count = zend_hash_num_elements(Z_ARRVAL_P(array));
	tmp = geo_array_ctor(element_count);

	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), entry) {
		if (!parse_point_pair(entry, &lon, &lat)) {
			goto failure;
		}

		tmp->x[i] = lon;
		tmp->y[i] = lat;
		tmp->status[i] = 1;

		i++;
	} ZEND_HASH_FOREACH_END();

	return tmp;

failure:
	geo_array_dtor(tmp);
	return NULL;
}

PHP_FUNCTION(polar_to_cartesian)
{
	// variable declarations
	// zend_parse_parameters call
	// convert data
	// call polar_to_cartesian
	// convert result to array and return
}

PHP_FUNCTION(cartesian_to_polar)
{
	// variable declarations
	// zend_parse_parameters call
	// convert data
	// call cartesian_to_polar
	// convert result to array and return
}

PHP_FUNCTION(rdp_simplify)
{
	zval      *points_array;
	double     epsilon;
	geo_array *points;

	int        i;
	zval       pair;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zd", &points_array, &epsilon) == FAILURE) {
		return;
	}
					
	if (Z_TYPE_P(points_array) != IS_ARRAY) {
		return;
	}

	points = geo_hashtable_to_array(points_array TSRMLS_CC);
	if (!points) {
		return;
	}

	rdp_simplify(points, epsilon, 0, points->count - 1);

	array_init(return_value);

	for (i = 0; i < points->count; i++) {
		if (points->status[i]) {
			array_init(&pair);
			add_next_index_double(&pair, points->x[i]);
			add_next_index_double(&pair, points->y[i]);
			add_next_index_zval(return_value, &pair);
		}
	}

	geo_array_dtor(points);
}

ZEND_BEGIN_ARG_INFO_EX(rdp_simplify_args, 0, 0, 2)
	ZEND_ARG_INFO(0, pointsArray)
	ZEND_ARG_INFO(0, epsilon)
ZEND_END_ARG_INFO()

const zend_function_entry geospatial_functions[] = {
	PHP_FE(rdp_simplify, rdp_simplify_args)
	{ NULL, NULL, NULL }
};

zend_module_entry geospatial_module_entry = {
	STANDARD_MODULE_HEADER,
	"geospatial",
	geospatial_functions,
	PHP_MINIT(geospatial),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(geospatial),
	PHP_GEOSPATIAL_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GEOSPATIAL
ZEND_GET_MODULE(geospatial)
#endif

PHP_MINIT_FUNCTION(geospatial)
{
	/*
	REGISTER_DOUBLE_CONSTANT("GEO_DIAMETER", GEO_DIAMETER, CONST_CS|CONST_PERSISTENT);
	*/
	return SUCCESS;
}

PHP_MINFO_FUNCTION(geospatial)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "Geospatial functions", "enabled");
	php_info_print_table_row(2, "Version", PHP_GEOSPATIAL_VERSION);
	php_info_print_table_end();
}
