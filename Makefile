piperate: piperate.c
	$(CC) $^ -o $@

clean:
	rm -f piperate

.PHONY: clean
