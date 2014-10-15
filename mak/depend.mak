
depend:
	mu depend $(INCLUDES) $(SOURCES) > depend.mak

-include depend.mak
