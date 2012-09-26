all :
	@echo
	@echo ==========================================
	@echo Compiling CommonLib
	@echo ==========================================
	$(MAKE) --directory="CommonLib" --file="CommonLib.mk"
	@echo
	@echo ==========================================
	@echo Compiling LinLib
	@echo ==========================================
	$(MAKE) --directory="LinLib" --file="LinLib.mk"
	@echo
	@echo ==========================================
	@echo Compiling CoreLib
	@echo ==========================================
	$(MAKE) --directory="CoreLib" --file="CoreLib.mk"
	@echo
	@echo ==========================================
	@echo Compiling WinEntry
	@echo ==========================================
	$(MAKE) --directory="WinEntry" --file="WinEntry.mk"
	@echo
	@echo ==========================================
	@echo  Success!
	@echo ==========================================
	@echo 

clean :
	@echo 
	@echo ==========================================
	@echo Cleaning
	@echo ==========================================
	@echo
	@echo === CommonLib ===
	$(MAKE) --directory="CommonLib" --file="CommonLib.mk" clean
	@echo
	@echo === LinLib ===
	$(MAKE) --directory="LinLib" --file="LinLib.mk" clean
	@echo 
	@echo === CoreLib ===
	$(MAKE) --directory="CoreLib" --file="CoreLib.mk" clean
	@echo 
	@echo === WinEntry ===
	$(MAKE) --directory="WinEntry" --file="WinEntry.mk" clean
	@echo
	@echo ==========================================
	@echo  Cleaning success!
	@echo ==========================================
	@echo 
