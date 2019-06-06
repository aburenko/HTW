const cacheName = 'note_cache';
const staticAssets = [
  '/',
  '/index.html',
  '/manifest.json',
  '/styles/main.css',
  '/styles/w3_schools.css',
  '/scripts/main.js',
  '/scripts/vexflow.js',
  '/img/icon.png',
  '/img/icon128.png',
  '/img/icon256.png',
  '/modules/alto.json',
  '/modules/bass.json',
  '/modules/treble.json'
  ];

self.addEventListener('install', async e => {
  const cache = await caches.open(cacheName);
  await cache.addAll(staticAssets);
  return self.skipWaiting();
});

self.addEventListener('activate', e => {
  self.clients.claim();
});

self.addEventListener('fetch', async e => {
  const req = e.request;
  const url = new URL(req.url);

  if (url.origin === location.origin) {
    e.respondWith(cacheFirst(req));
  } else {
    e.respondWith(networkAndCache(req));
  }
});

async function cacheFirst(req) {
  const cache = await caches.open(cacheName);
  const cached = await cache.match(req);
  return cached || fetch(req);
}

async function networkAndCache(req) {
  const cache = await caches.open(cacheName);
  try {
    const fresh = await fetch(req);
    await cache.put(req, fresh.clone());
    return fresh;
  } catch (e) {
    const cached = await cache.match(req);
    return cached;
  }
}