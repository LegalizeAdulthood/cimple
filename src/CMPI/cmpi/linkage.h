#ifndef _cimple_cmpi_linkage_h
#define _cimple_cmpi_linkage_h

#ifdef CIMPLECMPL_INTERNAL
# define CIMPLECMPI_LINKAGE CIMPLE_EXPORT
#else
# define CIMPLECMPI_LINKAGE CIMPLE_IMPORT
#endif

#endif /* _cimple_cmpi_linkage_h */
