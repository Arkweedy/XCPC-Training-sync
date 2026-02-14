// ==UserScript==
// @name         CF Verdict DOMjudge Style (cell overlay, sticky judging)
// @namespace    http://tampermonkey.net/
// @version      2.3
// @description  DOMjudge-like verdicts on Codeforces: per-row cell overlay; sticky JUDGING; time/memory columns keep blue cells but hide numbers.
// @author       Maxmilite + ChatGPT
// @license      GPLv3
// @match        https://codeforces.com/*
// @match        https://codeforc.es/*
// @run-at       document-idle
// @grant        GM_addStyle
// ==/UserScript==
(function () {
  "use strict";

  const CSS = `
/* 覆盖层：整格绝对居中显示判词 */
td.dj-cell { position: relative !important; }
td.dj-cell::after{
  content: attr(data-dj-label);
  font-weight: bold;
  position:absolute; left:50%; top:50%;
  transform: translate(-50%,-50%);
  white-space:nowrap; pointer-events:none; z-index:2;
}
/* DOMjudge 颜色 */
td.dj-cell[data-dj-type="ok"]::after      { color:#009900 !important; }
td.dj-cell[data-dj-type="wa"]::after      { color:#ff0000 !important; }
td.dj-cell[data-dj-type="tle"]::after     { color:#ff6600 !important; }
td.dj-cell[data-dj-type="re"]::after      { color:#9900cc !important; }
td.dj-cell[data-dj-type="ce"]::after      { color:#0066cc !important; }
td.dj-cell[data-dj-type="pending"]::after { color:#666666 !important; }
td.dj-cell[data-dj-type="judging"]::after { color:#666666 !important; }

/* 让状态格里的原内容不可见，但不影响点击 */
td.dj-cell *{ color:transparent !important; text-shadow:none !important; opacity:0 !important; }
td.dj-cell .test{ display:none !important; }

/* —— 这里是你要的改动：恢复时间/内存两列，但隐藏数值 —— */
/* 恢复列本体（不要隐藏列） */
td.time-consumed-cell, th.time-consumed-cell,
td.memory-consumed-cell, th.memory-consumed-cell{
  display: table-cell !important;
}
/* 隐藏具体数值/图标，保留单元格蓝底样式与布局 */
td.time-consumed-cell, td.memory-consumed-cell{
  position:relative; color:transparent !important; text-shadow:none !important;
}
td.time-consumed-cell *, td.memory-consumed-cell *{
  opacity:0 !important; pointer-events:none !important;
}
/* 如果想放一个占位符（如短横线），取消下一段注释：
td.time-consumed-cell::after, td.memory-consumed-cell::after{
  content:"—"; color:#889 !important; position:absolute; left:50%; top:50%;
  transform:translate(-50%,-50%); pointer-events:none; white-space:nowrap;
}
*/

/* 详情页继续隐藏 Time/Memory 属性块（按你之前的习惯） */
div.property-time, div.property-memory{ display:none !important; }

/* 右上角提示 */
#jGrowl{ display:none !important; }
`.trim();

  if (typeof GM_addStyle === 'function') GM_addStyle(CSS);
  else { const st = document.createElement('style'); st.textContent = CSS; document.head.appendChild(st); }

  // ========= 判词分类 + 粘性 JUDGING（沿用 2.1/2.2 的稳定实现） =========
  const FINAL = new Set(["OK","COMPILATION_ERROR","WRONG_ANSWER","TIME_LIMIT_EXCEEDED","RUNTIME_ERROR","MEMORY_LIMIT_EXCEEDED","IDLENESS_LIMIT_EXCEEDED","CRASHED","CHALLENGED","SKIPPED","PARTIAL"]);
  const sticky = new Set();

  const getSubmissionId = el => el.closest('tr[data-submission-id]')?.getAttribute('data-submission-id') || null;
  const findStatusCell = tr => tr.querySelector('td.status-cell, td.status') || tr.cells[5] || tr;
  const findVerdictNode = cell =>
    cell.querySelector('[submissionverdict], [data-submission-verdict]') ||
    cell.querySelector('.verdict-accepted, .verdict-rejected, .verdict-waiting') ||
    cell.querySelector('.submissionVerdictWrapper .verdict, .submissionVerdictWrapper span') ||
    Array.from(cell.querySelectorAll('span, a, div')).find(el =>
      /accepted|wrong answer|time limit|compilation|runtime|memory|idleness|running|testing|in queue|judging/i.test(el.textContent || "")
    ) || cell;

  function classify(node){
    const sv  = node.getAttribute('submissionverdict') || node.getAttribute('data-submission-verdict') || "";
    const cls = node.className || "";
    const txt = (node.textContent || "").toLowerCase();
    const sub = getSubmissionId(node);

    if (sv && FINAL.has(sv)) {
      if (sub) sticky.delete(sub);
      switch (sv) {
        case "OK": return {t:"ok",  l:"CORRECT"};
        case "COMPILATION_ERROR": return {t:"ce", l:"COMPILER-ERROR"};
        case "WRONG_ANSWER": return {t:"wa", l:"WRONG-ANSWER"};
        case "TIME_LIMIT_EXCEEDED": return {t:"tle", l:"TIMELIMIT"};
        default: return {t:"re", l:"RUN-ERROR"};
      }
    }
    if (/\bverdict-accepted\b/.test(cls)) { if (sub) sticky.delete(sub); return {t:"ok",  l:"CORRECT"}; }
    if (/\bverdict-rejected\b/.test(cls)) {
      if (/time limit/.test(txt))  { if (sub) sticky.delete(sub); return {t:"tle", l:"TIMELIMIT"}; }
      if (/wrong answer/.test(txt)){ if (sub) sticky.delete(sub); return {t:"wa",  l:"WRONG-ANSWER"}; }
      if (/compilation/.test(txt)) { if (sub) sticky.delete(sub); return {t:"ce",  l:"COMPILER-ERROR"}; }
      if (/memory|runtime|idleness|crash/.test(txt)) { if (sub) sticky.delete(sub); return {t:"re",  l:"RUN-ERROR"}; }
      if (sub) sticky.delete(sub); return {t:"re", l:"RUN-ERROR"};
    }
    if (/\bverdict-waiting\b/.test(cls)) {
      const running = /running|testing|on test|judging/.test(txt);
      if (sub && running) sticky.add(sub);
      return {t: (sub && sticky.has(sub)) || running ? "judging" : "pending",
              l: (sub && sticky.has(sub)) || running ? "JUDGING" : "PENDING"};
    }
    if (/accepted|ok/.test(txt))             { if (sub) sticky.delete(sub); return {t:"ok",  l:"CORRECT"}; }
    if (/wrong answer/.test(txt))            { if (sub) sticky.delete(sub); return {t:"wa",  l:"WRONG-ANSWER"}; }
    if (/time limit/.test(txt))              { if (sub) sticky.delete(sub); return {t:"tle", l:"TIMELIMIT"}; }
    if (/compilation/.test(txt))             { if (sub) sticky.delete(sub); return {t:"ce",  l:"COMPILER-ERROR"}; }
    if (/memory|runtime|idleness|crash/.test(txt)) { if (sub) sticky.delete(sub); return {t:"re",  l:"RUN-ERROR"}; }
    const running = /running|testing|on test|judging/.test(txt);
    const inQueue = /in queue|queue/.test(txt);
    if (sub && running) sticky.add(sub);
    return {t: (sub && sticky.has(sub)) || running ? "judging" : "pending",
            l: (sub && sticky.has(sub)) || running ? "JUDGING" : (inQueue ? "PENDING" : "PENDING")};
  }

  function processRow(tr){
    const cell = findStatusCell(tr);
    if (!cell) return;
    const node = findVerdictNode(cell);
    const {t, l} = classify(node);
    cell.classList.add('dj-cell');
    cell.setAttribute('data-dj-type', t);
    cell.setAttribute('data-dj-label', l);
  }

  function refresh(){
    document.querySelectorAll('tr[data-submission-id]').forEach(processRow);
    // 详情页等非表格位置
    document.querySelectorAll('.submissionVerdictWrapper, .verdict-accepted, .verdict-rejected, .verdict-waiting, [submissionverdict], [data-submission-verdict]')
      .forEach(el => {
        if (el.closest('tr[data-submission-id]')) return;
        const host = el.closest('.submissionVerdictWrapper') || el.parentElement || el;
        const {t, l} = classify(el);
        host.classList.add('dj-cell');
        host.setAttribute('data-dj-type', t);
        host.setAttribute('data-dj-label', l);
      });
  }

  refresh();
  let scheduled=false;
  const mo=new MutationObserver(()=>{ if(scheduled) return; scheduled=true; requestAnimationFrame(()=>{scheduled=false; refresh();}); });
  mo.observe(document.body,{childList:true,subtree:true});
  setInterval(refresh,500);
})();
