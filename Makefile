.PHONY: clean All

All:
	@echo "----------Building project:[ SCUnit - Release ]----------"
	@cd "SCUnit" && "$(MAKE)" -f  "SCUnit.mk"
clean:
	@echo "----------Cleaning project:[ SCUnit - Release ]----------"
	@cd "SCUnit" && "$(MAKE)" -f  "SCUnit.mk" clean
