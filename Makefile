.PHONY: clean All

All:
	@echo "----------Building project:[ main - Debug ]----------"
	@"$(MAKE)" -f  "main.mk"
clean:
	@echo "----------Cleaning project:[ main - Debug ]----------"
	@"$(MAKE)" -f  "main.mk" clean
