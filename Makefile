.PHONY: clean All

All:
	@echo "----------Building project:[ SCUnitTest - Debug ]----------"
	@cd "SCUnitTest" && "$(MAKE)" -f  "SCUnitTest.mk"
clean:
	@echo "----------Cleaning project:[ SCUnitTest - Debug ]----------"
	@cd "SCUnitTest" && "$(MAKE)" -f  "SCUnitTest.mk" clean
