from distutils.core import setup, Extension

setup(
   name='nanogui',
   version='1.0',
   description='Python bindings for the C++ GUI library nanogui.',
   author='Vincent Moeykens',
   author_email='vincent@beta.team',
   ext_modules=[Extension('bin', ['libnanogui.so', 'nanogui.cp37-win_amd64.pyd', 'nanogui.dll', 'nanogui.so'])],
)
