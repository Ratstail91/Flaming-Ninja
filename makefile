#for use on Windows:

#MKDIR=mkdir
#RM=del /y

OUTDIR=out

all: $(OUTDIR)
	$(MAKE) -C common
	$(MAKE) -C src

debug: export CXXFLAGS+=-g
debug: clean all

release: export CXXFLAGS+=-static-libgcc -static-libstdc++
release: clean all package

#For use on my machine ONLY
package:
	rar a -r -ep Ninja.rar $(OUTDIR)/*.exe  $(OUTDIR)/*.dll

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
ifeq ($(OS),Windows_NT)
	$(RM) *.o *.a *.exe
else ifeq ($(shell uname), Linux)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	rm -f -v $(OUT)
endif

rebuild: clean all
