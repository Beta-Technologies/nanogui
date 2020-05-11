from setuptools import setup

setup(
   name='nanogui',
   version='1.0',
   description='Python bindings for the C++ GUI library nanogui.',
   author='Vincent Moeykens',
   author_email='vincent@beta.team',
   packages=['nanogui',],
   package_dir={'nanogui': 'bin',},
   package_data={'nanogui': ['nanogui.cp37-win_amd64.pyd', 'nanogui.dll', 'nanogui.so', 'libnanogui.so'],},
)
