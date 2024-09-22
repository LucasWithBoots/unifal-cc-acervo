---
layout: default
title: Contato
permalink: /docs/contato
nav_order: 3
---

<head>
<script async defer src="https://eu.altcha.org/js/latest/altcha.min.js" type="module"></script>
  <!-- Your code -->
</head>

<form>
  <altcha-widget
    challengeurl="https://eu.altcha.org/api/v1/challenge?apiKey=ckey_01e5ad39ed0ff69acdf508456e45"
  ></altcha-widget>
</form>

<!-- Replace the variables below. -->
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
