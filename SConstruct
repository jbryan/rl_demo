# vim:ft=python
env = Environment();

pkg_config_libs = [
  'sdl',
  'gl',
  'glu',
]

#----------------------------------------
# Environment
#----------------------------------------
env.ParseConfig('pkg-config --cflags --libs %s' % " ".join(pkg_config_libs))

env.Append(
  CXXFLAGS=[
    '-O3',
    '-DNDEBUG',
  ]
)

sources = Glob("*.cpp")
object_list = env.Object(source = sources)

ex_point_pf = env.Program("relearn", source=object_list)

