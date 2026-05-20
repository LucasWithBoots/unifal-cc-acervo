---
title: Home
layout: home
nav_order: 0
---

{% assign pdf_files = site.static_files | where_exp: "file", "file.path contains '/docs/disciplinas/' and file.extname != '.md' and file.extname != '.html'" %}

# **Acervo da Ciência da Computação**

Central de Provas, Trabalhos, Atividades e Materiais de Estudo.
{: .fs-6 .fw-300 }

Temos {{ pdf_files | size }} arquivos no nosso acervo! 🎉
{: .fs-5 .fw-300 }

<span class="fs-5">
[Acessar Disciplinas](./docs/disciplinas){: .btn .btn-purple .mr-2}
[Veja no Github](https://github.com/LucasWithBoots/unifal-cc-acervo){: .btn target="_blank"}
</span>

{: .destaque }

> **Tem uma prova que não está no acervo?** Me envie pelo [WhatsApp](https://wa.me/5527996610631). Antes de publicar, removo qualquer dado pessoal da prova para preservar sua identidade.

---

{: .aviso }

> Este acervo é uma iniciativa independente e não possui nenhuma afiliação, parceria ou vínculo oficial com a [Universidade Federal de Alfenas (UNIFAL-MG)]. Todo o conteúdo disponível aqui é de responsabilidade exclusiva dos seus administradores e visa apenas fornecer um recurso adicional para auxiliar os estudantes em seus estudos.
>
> O acervo não possui qualquer caráter econômico, apenas educacional. O autor se dispõe a remover qualquer material não autorizado mediante solicitação.
>
> A [UNIFAL-MG] não endossa, valida ou se responsabiliza pelas informações contidas neste site.

[Markdown]: https://daringfireball.net/projects/markdown/
[Jekyll]: https://jekyllrb.com/
[Universidade Federal de Alfenas (UNIFAL-MG)]: https://www.unifal-mg.edu.br/
[UNIFAL-MG]: https://www.unifal-mg.edu.br/
