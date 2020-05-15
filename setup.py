from setuptools import setup

setup(
    name='nanogui',
    version='1.0.0',
    description='Python bindings for the C++ GUI library nanogui.',
    author='Vincent Moeykens',
    author_email='vincent@beta.team',
    packages=['',],
    package_dir={'': 'bin',},
    package_data={'': ['nanogui.cp37-win_amd64.pyd', 'nanogui.dll', 'nanogui.so', 'libnanogui.so'],},
)