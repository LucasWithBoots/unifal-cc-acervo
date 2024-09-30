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
  document.addEventListener("DOMContentLoaded", function() {
    const altchaWidget = document.getElementById("altcha");
    
    // Verifica se o widget existe
    if (altchaWidget) {
      // Cria um observador para monitorar mudanças no atributo `data-state`
      const observer = new MutationObserver((mutations) => {
        mutations.forEach((mutation) => {
          if (mutation.attributeName === "data-state") {
            const state = altchaWidget.getAttribute("data-state");
            
            // Verifica se o estado mudou para 'verified'
            if (state === "verified") {
              console.log("Captcha verificado com sucesso!");
            } else if (state === "unverified") {
              console.log("Captcha não verificado.");
            }
          }
        });
      });

      // Inicia o observador, monitorando o atributo `data-state`
      observer.observe(altchaWidget, { attributes: true });
    }
  });
</script>
