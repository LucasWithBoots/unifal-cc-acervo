---
layout: default
title: Contato
permalink: /docs/contato
nav_order: 3
---

<head>
  <script src="https://www.google.com/recaptcha/enterprise.js?render=6Lcdk0sqAAAAAPAvw658xiPUO5ugeod0gqXV0RGQ"></script>
  <!-- Your code -->
</head>

<button class="g-recaptcha"
    data-sitekey="6Lcdk0sqAAAAAPAvw658xiPUO5ugeod0gqXV0RGQ"
    data-callback='onSubmit'
    data-action='submit'>
Submit
</button>

<!-- Replace the variables below. -->
<script>
  function onSubmit(token) {
    document.getElementById("demo-form").submit();
  }
</script>
