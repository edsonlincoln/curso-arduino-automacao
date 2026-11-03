#!/usr/bin/env python3
"""gerar_portal.py — gera docs/ (GitHub Pages), ZIP por aula e QR codes."""
import sys, re, html, shutil, pathlib, yaml, qrcode

cfg_path = pathlib.Path(sys.argv[1]).resolve()
raiz = cfg_path.parent
cfg = yaml.safe_load(cfg_path.read_text(encoding="utf-8"))
base = cfg["url_base"].rstrip("/")
c = cfg.get("cores", {})
docs, codigos, qrdir = raiz / "docs", raiz / "codigos", raiz / "qrcodes"
dl = docs / "downloads"
dl.mkdir(parents=True, exist_ok=True); qrdir.mkdir(exist_ok=True)
(docs / ".nojekyll").write_text("")

CSS = f"""
:root{{--p:{c.get('primaria','#F26B1D')};--e:{c.get('escura','#1E1E1E')};--f:{c.get('fundo','#F7F7F7')}}}
*{{box-sizing:border-box}}body{{margin:0;font-family:system-ui,Arial,sans-serif;background:var(--f);color:var(--e)}}
header{{background:var(--e);color:#fff;padding:16px 24px}}header a{{color:#fff;text-decoration:none}}
main{{max-width:900px;margin:auto;padding:24px}}h1,h2{{color:var(--e)}}
.card{{background:#fff;border-radius:10px;padding:16px 20px;margin:12px 0;box-shadow:0 1px 4px #0002}}
.btn{{display:inline-block;background:var(--p);color:#fff;padding:10px 16px;border-radius:8px;text-decoration:none;margin:4px 6px 4px 0;border:0;cursor:pointer;font-size:15px}}
.video{{position:relative;padding-top:56.25%}}.video iframe{{position:absolute;inset:0;width:100%;height:100%;border:0;border-radius:10px}}
pre{{background:#1e1e1e;color:#eee;padding:16px;border-radius:8px;overflow:auto;font-size:14px}}
ul.aulas a{{color:var(--e)}}footer{{text-align:center;padding:24px;font-size:13px;color:#777}}
"""

def embed(url):
    if not url: return ""
    m = re.search(r"(?:youtu\.be/|v=|embed/)([\w-]{11})", url)
    if m: return f"https://www.youtube.com/embed/{m.group(1)}"
    m = re.search(r"vimeo\.com/(\d+)", url)
    return f"https://player.vimeo.com/video/{m.group(1)}" if m else url

def pagina(titulo, corpo, nivel):
    volta = "../" * nivel
    return f"""<!DOCTYPE html><html lang="pt-BR"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1"><title>{html.escape(titulo)}</title>
<style>{CSS}</style></head><body><header><a href="{volta}index.html"><b>{html.escape(cfg['titulo'])}</b> · Área do Aluno</a></header>
<main>{corpo}</main><footer>E3Maker · www.e3maker.com.br</footer>
<script>function copiar(id){{navigator.clipboard.writeText(document.getElementById(id).innerText);alert('Código copiado!')}}</script>
</body></html>"""

indice = [f"<h1>{html.escape(cfg['titulo'])}</h1><p>Escolha a aula. Cada aula tem vídeo, código para a Arduino IDE e arquivos de apoio.</p>"]
for mod in cfg["modulos"]:
    indice.append(f"<div class='card'><h2>{html.escape(mod['titulo'])}</h2><ul class='aulas'>")
    for a in mod["aulas"]:
        aid, pasta = a["id"], codigos / mod["id"] / a["id"]
        ino = pasta / f"{aid}.ino"
        out = docs / mod["id"] / aid; out.mkdir(parents=True, exist_ok=True)
        (dl / aid).mkdir(exist_ok=True)
        partes = [f"<h1>{html.escape(a['titulo'])}</h1>"]
        if a.get("video"):
            partes.append(f"<div class='card video'><iframe src='{embed(a['video'])}' allowfullscreen></iframe></div>")
        else:
            partes.append("<div class='card'><p>🎬 Videoaula em breve nesta página.</p></div>")
        botoes = []
        if pasta.exists():
            shutil.make_archive(str(dl / aid), "zip", root_dir=pasta.parent, base_dir=aid)
            botoes.append(f"<a class='btn' href='../../downloads/{aid}.zip'>⬇ Baixar projeto (ZIP para Arduino IDE)</a>")
        if ino.exists():
            shutil.copy(ino, dl / aid / ino.name)
            botoes.append(f"<a class='btn' href='../../downloads/{aid}/{ino.name}' download>⬇ Só o .ino</a>")
        for arq in a.get("arquivos", []):
            if (pasta / arq).exists():
                shutil.copy(pasta / arq, dl / aid / arq)
                botoes.append(f"<a class='btn' href='../../downloads/{aid}/{arq}' download>📄 {html.escape(arq)}</a>")
        if a.get("wokwi"):
            botoes.append(f"<a class='btn' href='{a['wokwi']}' target='_blank'>▶ Simular no Wokwi</a>")
        botoes.append(f"<a class='btn' href='{cfg['repo']}/tree/main/codigos/{mod['id']}/{aid}' target='_blank'>Ver no GitHub</a>")
        partes.append("<div class='card'><h2>Arquivos</h2>" + "".join(botoes) +
                      "<p><small>Descompacte o ZIP e abra o arquivo .ino — a pasta já vem com o nome certo para a Arduino IDE.</small></p></div>")
        if ino.exists():
            partes.append(f"<div class='card'><h2>Código</h2><button class='btn' onclick=\"copiar('cod')\">Copiar código</button>"
                          f"<pre id='cod'>{html.escape(ino.read_text(encoding='utf-8'))}</pre></div>")
        (out / "index.html").write_text(pagina(a["titulo"], "".join(partes), 2), encoding="utf-8")
        url = f"{base}/{mod['id']}/{aid}/"
        qr = qrcode.QRCode(box_size=10, border=2); qr.add_data(url); qr.make(fit=True)
        qr.make_image(fill_color=c.get("escura", "#1E1E1E"), back_color="white").save(qrdir / f"{aid}.png")
        indice.append(f"<li><a href='{mod['id']}/{aid}/'>{html.escape(a['titulo'])}</a></li>")
        print("OK", aid, "→", url)
    indice.append("</ul></div>")
(docs / "index.html").write_text(pagina(cfg["titulo"], "".join(indice), 0), encoding="utf-8")
# QR geral do curso
qrcode.make(base + "/").save(qrdir / "_curso.png")
print("Portal gerado em docs/ · QR codes em qrcodes/")
