%$(OBJ) : %.cpp
	$(call make_obj)
	$(ECHONL)

%$(OBJ) : %.c
	$(call make_c_obj)
	$(ECHONL)
