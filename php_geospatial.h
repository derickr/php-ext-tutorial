#ifndef PHP_GEOSPATIAL_H
#define PHP_GEOSPATIAL_H

#define PHP_GEOSPATIAL_VERSION "0.1.1-dev"

extern zend_module_entry geospatial_module_entry;
#define phpext_geospatial_ptr &geospatial_module_entry

PHP_MINIT_FUNCTION(geospatial);
PHP_MINFO_FUNCTION(geospatial);

PHP_FUNCTION(rdp_simplify);

#endif /* PHP_GEOSPATIAL_H */

