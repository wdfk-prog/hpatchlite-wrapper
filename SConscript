# SConscript file for hpatchlite-wrapper package

from building import *
import os

# Get the absolute path of the current SConscript file
cwd = GetCurrentDir()

# --- Source Files ---
# Add all necessary source files for the build.
# We only need the core hpatch_lite implementation and the selected decompressor.
src = []
src += Glob('hpatch_impl.c')
src += Glob('HPatchLite/decompresser/tinyuz/tuz_dec.c')
src += Glob('HPatchLite/HDiffPatch/libHDiffPatch/HPatchLite/hpatch_lite.c')

# --- Include Paths ---
# Add all necessary include paths for the compiler.
# This ensures that #include directives can find the required header files.
inc = []
inc.append(cwd)
# Since HPatchLite is a submodule, all its internal paths are relative to its root.
hpatchlite_root = os.path.join(cwd, 'HPatchLite')
inc.append(hpatchlite_root)
inc.append(os.path.join(hpatchlite_root, 'HDiffPatch/libHDiffPatch/HPatchLite'))
inc.append(os.path.join(hpatchlite_root, 'HDiffPatch/libHDiffPatch/HPatch'))

# Add decompressor source files only if they are enabled in the configuration.
if GetDepend(['PKG_HPATCHLITE_DECOMPRESSER_TUZ']):
    src += Glob('HPatchLite/tinyuz/decompress/tuz_dec.c')
    inc.append(os.path.join(hpatchlite_root, 'tinyuz/decompress'))

# --- Define the Component Group --- 
# Define a group named 'hpatchlite' that will be added to the build system.
# This group will only be compiled if the Kconfig option 'PKG_USING_HPATCHLITE' is enabled.
group = DefineGroup('hpatchlite-wrapper', src, depend=['PKG_USING_HPATCHLITE'], CPPPATH=inc)

# Return the defined group to the build system
Return('group')