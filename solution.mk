all :
	$(MAKE) --directory="prog" --file="proj.mk"

clean :
	$(MAKE) --directory="prog" --file="proj.mk" clean
