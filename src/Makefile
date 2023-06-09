EE_BIN = main.elf
SRC_FILES = $(shell find $(PREFIX) -name "*.cc" -o -name "*.cpp" -o -name "*.c")
EE_OBJS = $(patsubst %.cc, %.o, $(SRC_FILES))
EE_OBJS := $(patsubst %.c, %.o, $(EE_OBJS))
EE_OBJS := $(patsubst %.cpp, %.o, $(EE_OBJS))
EE_INCS := -Iinclude $(EE_INCS)
EE_LIBS = -ldraw -lgraph -lmath3d -lpacket -ldma -lpad -lc -lstdc++ -lgs -ldebug -leedebug -lpacket2
EE_OPTFLAGS = -O3 -g
EE_WARNFLAGS = -Wall -Wno-unused-function -Wno-unused-variable
LINKFLAGS	= -O3 -Wl,-zmax-page-size=128

OUTPUT_DIR     = build
VU_OUTPUT_DIR  = vu
VU_PROGS = $(addprefix $(OUTPUT_DIR)/$(VU_OUTPUT_DIR)/, $(patsubst %.vcl, %.o, $(VCL_FILES)))

MKDIR_CMD = mkdir -p

#
# Vector Unit assembler:
#
PS2_VU_DVP = dvp-as

#
# openvcl = Vector Command Line preprocessor.
# (get it at: https://github.com/jsvennevid/openvcl)
#
# vclpp = Vector assembly preprocessor
# (get it at: https://github.com/glampert/vclpp)
PS2_VCL   = vcl
PS2_VCLPP = vclpp

#
# VCL/VU microprograms:
#
VCL_PATH  = $(PREFIX)vu1progs
VCL_FILES = color_triangles_clip_tris.vcl color_triangles_clip_verts.vcl draw_finish.vcl

EE_OBJS := $(VU_PROGS) $(EE_OBJS)

all: $(EE_BIN)
#	$(EE_STRIP) --strip-all $(EE_BIN)

# $(EE_BIN): $(VU_PROGS) $(EE_OBJS)
# 	$(shell echo "hello")
# $(QUIET) $(PS2_CC) $(PS2_LINKCMD) $(PS2_CFLAGS) -o \
# 	$(EE_BIN) $(OBJ_FILES) \
# 	$(VU_PROGS) $(PS2_LDFLAGS) $(PS2_LIBS)

#
# VU microprograms:
#
$(VU_PROGS): $(OUTPUT_DIR)/$(VU_OUTPUT_DIR)/%.o: $(OUTPUT_DIR)/$(VU_OUTPUT_DIR)/%.vsm
	$(PS2_VU_DVP) $< -o $@

$(OUTPUT_DIR)/$(VU_OUTPUT_DIR)/%.vsm:
	$(MKDIR_CMD) $(dir $@)
	$(PS2_VCLPP) $(VCL_PATH)/$*.vcl $(dir $@)$*.pp.vcl -j
	$(PS2_VCL) -o$@ $(dir $@)$*.pp.vcl

clean:
	rm -f $(EE_BIN) $(EE_OBJS)
	rm -rf $(OUTPUT_DIR)/$(VU_OUTPUT_DIR)

run: $(EE_BIN)
	ps2client -h $(PS2HOST) execee host:$(EE_BIN)

reset:
	ps2client -h $(PS2HOST) reset