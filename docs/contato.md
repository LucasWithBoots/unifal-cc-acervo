---
layout: default
title: Contato
permalink: /docs/contato
nav_order: 3
---

<script async defer src="https://cdn.jsdelivr.net/npm/altcha/dist/altcha.min.js" type="module"></script>

<form>
  <altcha-widget
    id="altcha"
    challengeurl="https://eu.altcha.org/api/v1/challenge?apiKey=ckey_01e5ad39ed0fe6c511365ea5baf7"
    spamfilter
  ></altcha-widget>
</form>

<script>
    document.querySelector('#altcha').addEventListener('statechange', (ev) => {
  // state can be: unverified, verifying, verified, error
  console.log('state:', ev.detail.state);
  if (ev.detail.state === 'verified') {
    // payload contains base64 encoded data for the server
    console.log('payload:', ev.detail.payload);
  }
});
</script>
