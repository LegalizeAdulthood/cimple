// meb: This code was once used to generate repository.h and repository.cpp.
// These declared/defined an array of meta-classes.

void gen_repository_header_file(const vector<string>& classes)
{
    gen_comment_block();
    nl();

    out("#ifndef _repository_h\n");
    out("#define _repository_h\n");
    nl();

    out("#include <cimple/cimple.h>\n");

    for (size_t i = 0; i < classes.size(); i++)
        out("#include \"%s.h\"\n", classes[i].c_str());

    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    out("CIMPLE_ENTRY_POINT void cimple_repository(\n");
    out("    const Meta_Class**& meta_classes,\n");
    out("    size_t& num_meta_classes);\n");
    nl();

    out("CIMPLE_NAMESPACE_END\n");
    nl();

    out("#endif /* _repository_h */\n");
}

void gen_repository_source_file(const vector<string>& classes)
{
    gen_comment_block();
    nl();

    out("#include <cimple/cimple.h>\n");
    out("#include \"repository.h\"\n");
    nl();

    out("CIMPLE_NAMESPACE_BEGIN\n");
    nl();

    out("static const Meta_Class* _meta_classes[] =\n");
    out("{\n");

    for (size_t i = 0; i < classes.size(); i++)
        out("    &%s::static_meta_class,\n", classes[i].c_str());

    out("};\n");
    nl();
    out("static const size_t _num_meta_classes = ");
    out("CIMPLE_ARRAY_SIZE(_meta_classes);\n");
    nl();

    out("CIMPLE_ENTRY_POINT void cimple_repository(\n");
    out("    const Meta_Class**& meta_classes,\n");
    out("    size_t& num_meta_classes)\n");
    out("{\n");
    out("   meta_classes = _meta_classes; \n");
    out("   num_meta_classes = _num_meta_classes; \n");
    out("}\n");
    nl();


    out("CIMPLE_NAMESPACE_END\n");
}

void gen_repository(const vector<string>& classes)
{
    //
    // Generate header:
    //

    {
        //
        // Open the file.
        //

        const char FILENAME[] = "repository.h";

        if ((_os = fopen(FILENAME, "wb")) == 0)
        {
            err("error: cannot open \"%s\"", FILENAME);
            exit(1);
        }

        //
        // Generate file.
        //

        gen_repository_header_file(classes);

        printf("created %s\n", FILENAME);

        //
        // Close the file.
        //

        fclose(_os);
    }

    //
    // Generate source:
    //

    {
        //
        // Open the file.
        //

        const char FILENAME[] = "repository.cpp";

        if ((_os = fopen(FILENAME, "wb")) == 0)
        {
            err("error: cannot open \"%s\"", FILENAME);
            exit(1);
        }

        //
        // Generate file.
        //

        gen_repository_source_file(classes);

        //
        // Generate entry point: cimple_repository()
        //

        printf("Created %s\n", FILENAME);

        //
        // Close the file.
        //

        fclose(_os);
    }
}
