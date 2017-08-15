.PHONY: clean All

All:
	@echo "----------Building project:[ SCUnitTest - Release ]----------"
	@cd "SCUnitTest" && "$(MAKE)" -f  "SCUnitTest.mk"
clean:
	@echo "----------Cleaning project:[ SCUnitTest - Release ]----------"
	@cd "SCUnitTest" && "$(MAKE)" -f  "SCUnitTest.mk" clean
