from setuptools import setup
import sys
import platform


class PyVersionException(Exception):
    """Exception for platform and python version errors"""
    def __init__(self, message="Your platform and Python Version combination is not supported"):
        self.message = message
        super().__init__(self.message)

distributions = {
    'Windows': {
        6: {
            '': ['nanogui.cp36-win_amd64.pyd', 'nanogui.dll', 'vcruntime140_1.dll']
        },
        7: {
            '': ['nanogui.cp37-win_amd64.pyd', 'nanogui.dll', 'vcruntime140_1.dll']
        },
        8: {
            '': ['nanogui.cp38-win_amd64.pyd', 'nanogui.dll', 'vcruntime140_1.dll']
        }
    },
    'Linux': {
        6: {
            '': ['nanogui.cpython-36m-x86_64-linux-gnu.so', 'libnanogui.so']
        },
        7: {
            '': ['nanogui.cpython-37m-x86_64-linux-gnu.so', 'libnanogui.so']
        },
        8: {
            '': ['nanogui.cpython-38-x86_64-linux-gnu.so', 'libnanogui.so']
        }
    },
    'Darwin': {
        6: {
            '': ['nanogui.cpython-36m-darwin.so', 'libnanogui.dylib']
        },
        7: {
            '': ['nanogui.cpython-37m-darwin.so', 'libnanogui.dylib']
        },
        8: {
            '': ['nanogui.cpython-38m-darwin.so', 'libnanogui.dylib']
        }
    }
}

try:
    os_distributions = distributions[platform.system()]
except KeyError:
    # don't use f-strings to prevent syntax error on older Python versions
    sys.exit('Unrecognized platform: ' + platform.system())

if platform.system() == 'Darwin' and sys.version_info[0] == 3 and sys.version_info[1] == 8:
    raise PyVersionException

try:
    if sys.version_info[0] != 3:
        raise KeyError
    package_data = os_distributions[sys.version_info[1]]
except KeyError:
    # don't use f-strings to prevent syntax error on older Python versions
    sys.exit('Currently we only support Python 3.6, 3.7 or 3.8, but you are using ' + sys.version)

setup(
    name='nanogui',
    python_requires='>=3.6, <3.9',
    version='1.1.0',
    description='Python bindings for the C++ GUI library nanogui.',
    author='BETA Technologies',
    author_email='info@beta.team',
    packages=[''],
    package_dir={'': 'bin'},
    package_data=package_data,
)
