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
  // Adiciona um event listener para quando o captcha for verificado com sucesso
  document.getElementById('altcha').addEventListener('altcha-verified', function() {
    console.log('Captcha resolvido corretamente!');
    // Aqui você pode adicionar outras ações, como desbloquear um botão de submit
  });
</script>
