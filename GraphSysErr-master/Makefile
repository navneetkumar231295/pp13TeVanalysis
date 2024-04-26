#
#
#
NAME		:= GSE
VERSION		:= 0.10-2
CLASSES		:= GraphSysErr
TESTS		:= tests/DrawStyles.C		\
		   tests/TestMaker.C		\
		   tests/FlipTest.C		\
		   tests/SplitInput.C		\
		   tests/TestImport.C		\
		   tests/TestMultiImport.C	\
		   tests/WriteTests.C		\
		   tests/Load.C
DATA		:= inputs/dndeta_pa.input	\
		   inputs/kstar_pt.input	\
		   inputs/large.input		\
		   inputs/sample.input		
DISTS		:= $(CLASSES:%=%.C) $(TESTS) $(DATA) \
		   Makefile README.md BNF.md Doxyfile
DEST		:= "~/www/public_html/root/gse"
DHOST		:= lxplus.cern.ch
ROOT		:= root
ROOTFLAGS	:= -l -b -q
ROOTVER         := $(subst .,, \
		    $(subst /,, \
                      $(dir $(shell root-config --version))))
ROOTVER		:= $(shell if test $$(($(ROOTVER) % 2)) -eq 1 ; \
		      then echo $$(($(ROOTVER)-1)) ; else \
	                echo $(ROOTVER) ; fi)
TEST_FLAGS	:= $(shell if test $(ROOTVER) -ge 600 ; then \
			echo "tests/Load.C\(1,0\)" ; fi)
# ifeq ($(ROOTVER), )
ROOTTAG		:= https://root.cern.ch/doc/master/ROOT.tag
# else
# ROOTTAG		:= https://root.cern.ch/doc/$(ROOTVER)/ROOT.tag
# endif

# --- General stuff --------------------------------------------------
all: doc

ver:
	@echo $(ROOTVER)

clean:
	rm -f *~ 			\
	      *.png 			\
	      *.input			\
	      *.root			\
	      *.log			\
	      *.pcm			\
	      ds_*_*.C			\
	      ds_*_*.input		\
	      core			\
	      GraphSysErr_C.* 		\
	      doxygen_objdb*		\
	      doxygen_sqlite3.db 	\
	      $(NAME)-$(VERSION).tar.gz \
	      inputs/*_again.*		\
	      inputs/*.png		\
	      inputs/*.root		\
	      tests/*~ 			\
	      tests/*.pcm		\
	      tests/*_C.so		\
	      tests/*_C.d		\
	      ROOT.tag
	rm -rf html

# --- Building -------------------------------------------------------
GraphSysErr_C.d:GraphSysErr_C.so
	@if test -f $@ ; then touch $@ ; \
		else rm -f $< ; $(MAKE) $(MAKEFLAGS) $< ; fi
GraphSysErr_C.so:tests/Load.C GraphSysErr.C 
	$(ROOT) $(ROOTFLAGS) $< 


# --- Documentation --------------------------------------------------
DrawStyles.png:tests/DrawStyles.C
	$(ROOT) $(ROOTFLAGS) $(TEST_FLAGS) $< 

%.png:inputs/%.input tests/TestImport.C GraphSysErr.C
	$(ROOT) $(ROOTFLAGS) tests/Load.C tests/TestImport.C\(\"$<\"\)

Example.png:Example.C GraphSysErr.C
	$(ROOT) $(ROOTFLAGS) $(TEST_FLAGS) $< 

ROOT.tag:
	if test $(ROOTVER) -ge 600 ; then \
	  wget -nv $(ROOTTAG) -O - | gzip -dc - > $@;  else \
	  echo "<?xml version='1.0' standalone='yes' ?><tagfile></tagfile>" \
	    > $@  ; fi

doc:Doxyfile DrawStyles.png Example.png dndeta_pa.png ROOT.tag
	doxygen $<


# --- Making distributions -------------------------------------------
distdir:
	mkdir -p $(NAME)-$(VERSION)
	$(foreach d, $(DISTS), \
	  mkdir -p $(NAME)-$(VERSION)/$(dir $(d));\
	  cp $(d) $(NAME)-$(VERSION)/$(d) ;)

dist:distdir
	tar -czf $(NAME)-$(VERSION).tar.gz $(NAME)-$(VERSION)
	rm -rf $(NAME)-$(VERSION)

# --- Some examples and tests ----------------------------------------
test:	inputs/arxiv_1412.6828_again.input		\
	inputs/large_again.input			\
	inputs/sample_again.input			\
	check05.input

inputs/arxiv_1412.6828_again.input:tests/ManyTables.C \
				   inputs/arxiv_1412.6828.input \
				   GraphSysErr_C.so
	$(ROOT) $(ROOTFLAGS) $(TEST_FLAGS) $<

inputs/large_again.input:tests/TestLargeImport.C 	\
			 inputs/large.input		\
			 GraphSysErr_C.so
	$(ROOT) $(ROOTFLAGS) $(TEST_FLAGS) $<

inputs/sample_again.input:tests/TestMultiImport.C	\
			  inputs/sample.input		\
			  GraphSysErr_C.so		
	$(ROOT) $(ROOTFLAGS) $(TEST_FLAGS) $<

check05.input \
check04.input \
check03.input \
check02.input \
check01.input \
test05.input \
test04.input \
test03.input \
test02.input : test01.input
	@if test -f $@ ; then touch $@ ; \
		else rm -f $< ; $(MAKE) $(MAKEFLAGS) $< ; fi

test01.input:tests/WriteTests.C
	$(ROOT) $(ROOTFLAGS) $(TEST_FLAGS) $<

#
# EOF
# 

