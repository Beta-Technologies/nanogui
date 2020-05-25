from setuptools import setup
import sys
import platform

if sys.version_info[1] != 6 and sys.version_info[1] != 7:
    raise Exception("Must be using Python 3.6 or 3.7")

if platform.system() not in ['Windows', 'Darwin', 'Linux']:
    raise Exception("Unrecognized Platform")

distributions = {
    'Windows': {
        6: {
            '': ['nanogui.cp36-win_amd64.pyd', 'nanogui.dll']
        },
        7: {
            '': ['nanogui.cp37-win_amd64.pyd', 'nanogui.dll']
        }
    },
    'Linux': {
        6: {
            '': ['nanogui.cpython-36m-x86_64-linux-gnu.so', 'libnanogui.so']
        },
        7: {
            '': ['nanogui.cpython-37m-x86_64-linux-gnu.so', 'libnanogui.so']
        }
    },
    'Darwin': {
        6: {
            '': ['nanogui.cpython-36m-darwin.so', 'libnanogui.dylib']
        },
        7: {
            '': ['nanogui.cpython-37m-darwin.so', 'libnanogui.dylib']
        }
    }
}

package_data = distributions[platform.system()][sys.version_info[1]]

setup(
    name='nanogui',
    version='1.1.0',
    description='Python bindings for the C++ GUI library nanogui.',
    author='Vincent Moeykens',
    author_email='vincent@beta.team',
    packages=['',],
    package_dir={'': 'bin',},
    package_data=package_data,
)

