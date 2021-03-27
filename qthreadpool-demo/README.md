qthreadpool-demo - Framento de código ilustrativo del uso del _pool_ de hilos [QThreadPool](http://qt-project.org/doc/qt-5.0/qtcore/qthreadpool.html) en Qt.
<p xmlns:dct="http://purl.org/dc/terms/">
  <a rel="license"
     href="http://creativecommons.org/publicdomain/zero/1.0/">
    <img src="http://i.creativecommons.org/p/zero/1.0/80x15.png" style="border-style: none;" alt="CC0" />
  </a>
  En medida de lo que permita la ley,
  <a rel="dct:publisher"
     href="http://jmtorres.webs.ull.es//">
    <span property="dct:title">Jesús Torres</span></a>
  ha renunciado a todos los derechos de autor y los derechos conexos o relacionados con este código.
</p>

### qthreadpool-demo

El programa básicamente genera dos vectores de números aleatorios y calcula su producto escalar, paralelizando ambas tareas por medio del _pool_ de hilos de Qt.

Por defecto el _pool_ tiene tantos hilos como núcleos de CPU hay en el sistema. Para ajustar el tamaño del _pool_ con el objeto de ver su efecto sobre el rendimiento, basta con descomentar [main.cppi#L101](main.cpp#L101) y ajustar el valor. Obviamente, por lo general, el valor óptimo estará entorno al número de núcleos disponibles en el sistema.

-- Jesús Torres <jmtorres@ull.es>
