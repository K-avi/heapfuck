TARGET:= heapfuck
TEST :=test

ALLPROGS= $(TARGET) $(TEST)

.PHONY:	all clean

all: $(ALLPROGS)
progs: $(PROGRAMS)

$(TEST): 
	$(MAKE) -C src/ ../test

$(TARGET): 
	$(MAKE) -C src/ ../heapfuck


clean:
	$(MAKE) -C src/ clean
	rm -f $(ALLPROGS)

.PHONY: clean