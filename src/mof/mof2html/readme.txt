This program generates HTML output files from MOF files.  It was written 
originally as a test of the ability to compile complete DMTF schemas using 
the CIMPLE compiler but also serves as a way to generate HTML output for 
the schemas.  

Running this against a CIM schema produces an index that lists all of the
classes in the schema with hyperlinks to an html file for each class.

Note that to date there is not output generator for instances.

The output files are directed to the current working directory.  
The program does not attempt to clean out old files before writing the new
ones so it is best to manually clean the output directory before running
mof2html as any files that are not in the index are not pointed to and
therefore dead

Generally the input is:

     mof2html [options] [-I <include directory>]* <mof file>*

     
