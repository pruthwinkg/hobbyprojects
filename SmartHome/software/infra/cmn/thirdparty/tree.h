<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<meta name="robots" content="nofollow" />
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<meta name="generator" content="0.11-rc2 (d0ffee7f9877+)" />
<meta http-equiv="X-UA-Compatible" content="IE=8" />
<link rel="icon" href="/default/img/icon.png" type="image/png" />
<link rel="stylesheet" type="text/css" media="all"
    title="Default" href="/default/style.css" />
<link rel="alternate stylesheet" type="text/css" media="all"
    title="Paper White" href="/default/print.css" />
<link rel="stylesheet" type="text/css" href="/default/print.css" media="print" />
<link rel="stylesheet" type="text/css" href="/default/jquery.tooltip.css" />

<link rel="search" href="/opensearch"
    type="application/opensearchdescription+xml"
    title="OpenGrok Search for current project(s)" />
<script type="text/javascript" src="/jquery-1.4.4.min.js"></script>
<script type="text/javascript" src="/jquery.tooltip-1.3.pack.js"></script>

<script type="text/javascript" src="/utils.js"></script>
<title>Super User's BSD Cross Reference: /OpenBSD/sys/sys/tree.h</title>
</head><body>
<script type="text/javascript">/* <![CDATA[ */
    document.hash = 'null';document.rev = '';document.link = '/xref/OpenBSD/sys/sys/tree.h';document.annotate = false;
    document.domReady.push(function() {domReadyMast();});
    document.pageReady.push(function() { pageReadyMast();});
/* ]]> */</script>
<div id="page">
    <div id="whole_header">
        <form action="/search">
<div id="header">
<a href="/"><span id="MastheadLogo"></span></a>


    <div id="pagetitle"><span id="filename"
                    >Super User's BSD Cross Reference: tree.h</span></div>
</div>
<div id="Masthead">
    <tt><a href="/xref/">xref</a>: /<a href="/xref/OpenBSD/">OpenBSD</a>/<a href="/xref/OpenBSD/sys/">sys</a>/<a href="/xref/OpenBSD/sys/sys/">sys</a>/<a href="/xref/OpenBSD/sys/sys/tree.h">tree.h</a></tt>
</div>
<div id="bar">
    <ul>
        <li><a href="/"><span id="home"></span>Home</a></li>
    <li><a href="http://www.openbsd.org/cgi-bin/cvsweb/src/sys/sys/tree.h">CVSweb</a></li><li><a href="http://cvsweb.allbsd.org/cvsweb.cgi/src/sys/sys/tree.h?cvsroot=openbsd"
		 title='CVSweb from allbsd.org'>allbsd</a></li><li><a href="http://git.freebsd.your.org/gitweb/?p=openbsd.git;a=history;f=sys/sys/tree.h"><small>Gitweb history</small></a></li><li><a href="#" onclick="javascript:lntoggle();return false;"
            title="Show or hide line numbers (might be slower if file has more than 10 000 lines)."><span id="line"></span>Line#</a></li><li><a
            href="#" onclick="javascript:lsttoggle();return false;"
            title="Show or hide symbol list."><span id="defbox"></span>Navigate</a></li><li><a href="/raw/OpenBSD/sys/sys/tree.h"><span id="download"></span>Download</a></li><li><input type="text" id="search" name="q" class="q" />
            <input type="submit" value="Search" class="submit" /></li><li><input type="checkbox" name="path" value="/OpenBSD/sys/sys/" /> only in <b>tree.h</b></li>
        
    </ul>
    <input type="hidden" name="project" value="OpenBSD" />
</div>
        </form>
    </div>
<div id="content">
<script type="text/javascript">/* <![CDATA[ */
document.pageReady.push(function() { pageReadyList();});
/* ]]> */</script>

<div id="src">
    <pre><script type="text/javascript">/* <![CDATA[ */
function get_sym_list(){return [["Macro","xm",[["RBT_CHECK",984],["RBT_EMPTY",972],["RBT_ENTRY",789],["RBT_FIND",969],["RBT_FOREACH",986],["RBT_FOREACH_REVERSE",996],["RBT_FOREACH_REVERSE_SAFE",1001],["RBT_FOREACH_SAFE",991],["RBT_GENERATE",963],["RBT_GENERATE_AUGMENT",954],["RBT_GENERATE_INTERNAL",940],["RBT_HEAD",784],["RBT_INIT",966],["RBT_INITIALIZER",821],["RBT_INSERT",967],["RBT_LEFT",977],["RBT_MAX",974],["RBT_MIN",973],["RBT_NEXT",975],["RBT_NFIND",970],["RBT_PARENT",979],["RBT_POISON",983],["RBT_PREV",976],["RBT_PROTOTYPE",823],["RBT_REMOVE",968],["RBT_RIGHT",978],["RBT_ROOT",971],["RBT_SET_LEFT",980],["RBT_SET_PARENT",982],["RBT_SET_RIGHT",981],["RB_AUGMENT",334],["RB_BLACK",305],["RB_COLOR",318],["RB_EMPTY",320],["RB_ENTRY",307],["RB_FIND",723],["RB_FOREACH",730],["RB_FOREACH_REVERSE",740],["RB_FOREACH_REVERSE_SAFE",745],["RB_FOREACH_SAFE",735],["RB_GENERATE",397],["RB_GENERATE_INTERNAL",401],["RB_GENERATE_STATIC",399],["RB_HEAD",293],["RB_INF",719],["RB_INIT",301],["RB_INITIALIZER",298],["RB_INSERT",721],["RB_LEFT",315],["RB_MAX",728],["RB_MIN",727],["RB_NEGINF",718],["RB_NEXT",725],["RB_NFIND",724],["RB_PARENT",317],["RB_PREV",726],["RB_PROTOTYPE",378],["RB_PROTOTYPE_INTERNAL",382],["RB_PROTOTYPE_STATIC",380],["RB_RED",306],["RB_REMOVE",722],["RB_RIGHT",316],["RB_ROOT",319],["RB_ROTATE_LEFT",337],["RB_ROTATE_RIGHT",357],["RB_SET",322],["RB_SET_BLACKRED",328],["SPLAY_ASSEMBLE",107],["SPLAY_EMPTY",80],["SPLAY_ENTRY",71],["SPLAY_FIND",280],["SPLAY_FOREACH",287],["SPLAY_GENERATE",158],["SPLAY_HEAD",59],["SPLAY_INF",276],["SPLAY_INIT",67],["SPLAY_INITIALIZER",64],["SPLAY_INSERT",278],["SPLAY_LEFT",77],["SPLAY_LINKLEFT",95],["SPLAY_LINKRIGHT",101],["SPLAY_MAX",284],["SPLAY_MIN",282],["SPLAY_NEGINF",275],["SPLAY_NEXT",281],["SPLAY_PROTOTYPE",116],["SPLAY_REMOVE",279],["SPLAY_RIGHT",78],["SPLAY_ROOT",79],["SPLAY_ROTATE_LEFT",89],["SPLAY_ROTATE_RIGHT",83],["_SYS_TREE_H_",28]]],["Struct","xs",[["rb_entry",777],["rb_tree",773],["rb_type",767]]],["Function","xf",[["_rb_empty",798],["_rb_init",792]]]];} /* ]]> */</script><a class="l" name="1" href="#1">1</a><span class="c">/*  $OpenBSD: <a href="/s?path=tree.h&amp;project=OpenBSD">tree.h</a>,v 1.29 2017/07/30 19:27:20 deraadt Exp $   */</span>
<a class="l" name="2" href="#2">2</a><span class="c">/*
<a class="l" name="3" href="#3">3</a> * Copyright 2002 Niels Provos &lt;provos@citi.umich.edu&gt;
<a class="l" name="4" href="#4">4</a> * All rights reserved.
<a class="l" name="5" href="#5">5</a> *
<a class="l" name="6" href="#6">6</a> * Redistribution and use in source and binary forms, with or without
<a class="l" name="7" href="#7">7</a> * modification, are permitted provided that the following conditions
<a class="l" name="8" href="#8">8</a> * are met:
<a class="l" name="9" href="#9">9</a> * 1. Redistributions of source code must retain the above copyright
<a class="hl" name="10" href="#10">10</a> *    notice, this list of conditions and the following disclaimer.
<a class="l" name="11" href="#11">11</a> * 2. Redistributions in binary form must reproduce the above copyright
<a class="l" name="12" href="#12">12</a> *    notice, this list of conditions and the following disclaimer in the
<a class="l" name="13" href="#13">13</a> *    documentation <a href="/s?path=and/">and</a>/<a href="/s?path=and/or">or</a> other materials provided with the distribution.
<a class="l" name="14" href="#14">14</a> *
<a class="l" name="15" href="#15">15</a> * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
<a class="l" name="16" href="#16">16</a> * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
<a class="l" name="17" href="#17">17</a> * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
<a class="l" name="18" href="#18">18</a> * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
<a class="l" name="19" href="#19">19</a> * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
<a class="hl" name="20" href="#20">20</a> * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
<a class="l" name="21" href="#21">21</a> * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
<a class="l" name="22" href="#22">22</a> * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
<a class="l" name="23" href="#23">23</a> * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
<a class="l" name="24" href="#24">24</a> * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
<a class="l" name="25" href="#25">25</a> */</span>
<a class="l" name="26" href="#26">26</a>
<a class="l" name="27" href="#27">27</a>#<b>ifndef</b> <a class="d" href="#_SYS_TREE_H_">_SYS_TREE_H_</a>
<a class="l" name="28" href="#28">28</a>#<b>define</b> <a class="xm" name="_SYS_TREE_H_"/><a href="/s?refs=_SYS_TREE_H_&amp;project=OpenBSD" class="xm">_SYS_TREE_H_</a>
<a class="l" name="29" href="#29">29</a>
<a class="hl" name="30" href="#30">30</a>#<b>include</b> &lt;<a href="/s?defs=sys&amp;project=OpenBSD">sys</a>/<a href="/s?defs=_null&amp;project=OpenBSD">_null</a>.h&gt;
<a class="l" name="31" href="#31">31</a>
<a class="l" name="32" href="#32">32</a><span class="c">/*
<a class="l" name="33" href="#33">33</a> * This file defines data structures for different types of trees:
<a class="l" name="34" href="#34">34</a> * splay trees and red-black trees.
<a class="l" name="35" href="#35">35</a> *
<a class="l" name="36" href="#36">36</a> * A splay tree is a self-organizing data structure.  Every operation
<a class="l" name="37" href="#37">37</a> * on the tree causes a splay to happen.  The splay moves the requested
<a class="l" name="38" href="#38">38</a> * node to the root of the tree and partly rebalances it.
<a class="l" name="39" href="#39">39</a> *
<a class="hl" name="40" href="#40">40</a> * This has the benefit that request locality causes faster lookups as
<a class="l" name="41" href="#41">41</a> * the requested nodes move to the top of the tree.  On the other hand,
<a class="l" name="42" href="#42">42</a> * every lookup causes memory writes.
<a class="l" name="43" href="#43">43</a> *
<a class="l" name="44" href="#44">44</a> * The Balance Theorem bounds the total access time for m operations
<a class="l" name="45" href="#45">45</a> * and n inserts on an initially empty tree as O((m + n)lg n).  The
<a class="l" name="46" href="#46">46</a> * amortized cost for a sequence of m accesses to a splay tree is O(lg n);
<a class="l" name="47" href="#47">47</a> *
<a class="l" name="48" href="#48">48</a> * A red-black tree is a binary search tree with the node color as an
<a class="l" name="49" href="#49">49</a> * extra attribute.  It fulfills a set of conditions:
<a class="hl" name="50" href="#50">50</a> *  - every search path from the root to a leaf consists of the
<a class="l" name="51" href="#51">51</a> *    same number of black nodes,
<a class="l" name="52" href="#52">52</a> *  - each red node (except for the root) has a black parent,
<a class="l" name="53" href="#53">53</a> *  - each leaf node is black.
<a class="l" name="54" href="#54">54</a> *
<a class="l" name="55" href="#55">55</a> * Every operation on a red-black tree is bounded as O(lg n).
<a class="l" name="56" href="#56">56</a> * The maximum height of a red-black tree is 2lg (n+1).
<a class="l" name="57" href="#57">57</a> */</span>
<a class="l" name="58" href="#58">58</a>
<a class="l" name="59" href="#59">59</a>#<b>define</b> <a class="xm" name="SPLAY_HEAD"/><a href="/s?refs=SPLAY_HEAD&amp;project=OpenBSD" class="xm">SPLAY_HEAD</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>)                      \
<a class="hl" name="60" href="#60">60</a><b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> {                               \
<a class="l" name="61" href="#61">61</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>; <span class="c">/* root of the tree */</span>           \
<a class="l" name="62" href="#62">62</a>}
<a class="l" name="63" href="#63">63</a>
<a class="l" name="64" href="#64">64</a>#<b>define</b> <a class="xm" name="SPLAY_INITIALIZER"/><a href="/s?refs=SPLAY_INITIALIZER&amp;project=OpenBSD" class="xm">SPLAY_INITIALIZER</a>(<a href="/s?defs=root&amp;project=OpenBSD">root</a>)                     \
<a class="l" name="65" href="#65">65</a>    { <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> }
<a class="l" name="66" href="#66">66</a>
<a class="l" name="67" href="#67">67</a>#<b>define</b> <a class="xm" name="SPLAY_INIT"/><a href="/s?refs=SPLAY_INIT&amp;project=OpenBSD" class="xm">SPLAY_INIT</a>(<a href="/s?defs=root&amp;project=OpenBSD">root</a>) <b>do</b> {                       \
<a class="l" name="68" href="#68">68</a>    (<a href="/s?defs=root&amp;project=OpenBSD">root</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                    \
<a class="l" name="69" href="#69">69</a>} <b>while</b> (0)
<a class="hl" name="70" href="#70">70</a>
<a class="l" name="71" href="#71">71</a>#<b>define</b> <a class="xm" name="SPLAY_ENTRY"/><a href="/s?refs=SPLAY_ENTRY&amp;project=OpenBSD" class="xm">SPLAY_ENTRY</a>(<a href="/s?defs=type&amp;project=OpenBSD">type</a>)                       \
<a class="l" name="72" href="#72">72</a><b>struct</b> {                                \
<a class="l" name="73" href="#73">73</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=spe_left&amp;project=OpenBSD">spe_left</a>; <span class="c">/* left element */</span>           \
<a class="l" name="74" href="#74">74</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=spe_right&amp;project=OpenBSD">spe_right</a>; <span class="c">/* right element */</span>         \
<a class="l" name="75" href="#75">75</a>}
<a class="l" name="76" href="#76">76</a>
<a class="l" name="77" href="#77">77</a>#<b>define</b> <a class="xm" name="SPLAY_LEFT"/><a href="/s?refs=SPLAY_LEFT&amp;project=OpenBSD" class="xm">SPLAY_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)      (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>.<a href="/s?defs=spe_left&amp;project=OpenBSD">spe_left</a>
<a class="l" name="78" href="#78">78</a>#<b>define</b> <a class="xm" name="SPLAY_RIGHT"/><a href="/s?refs=SPLAY_RIGHT&amp;project=OpenBSD" class="xm">SPLAY_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)     (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>.<a href="/s?defs=spe_right&amp;project=OpenBSD">spe_right</a>
<a class="l" name="79" href="#79">79</a>#<b>define</b> <a class="xm" name="SPLAY_ROOT"/><a href="/s?refs=SPLAY_ROOT&amp;project=OpenBSD" class="xm">SPLAY_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>)        (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>
<a class="hl" name="80" href="#80">80</a>#<b>define</b> <a class="xm" name="SPLAY_EMPTY"/><a href="/s?refs=SPLAY_EMPTY&amp;project=OpenBSD" class="xm">SPLAY_EMPTY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>)       (<a class="d" href="#SPLAY_ROOT">SPLAY_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)
<a class="l" name="81" href="#81">81</a>
<a class="l" name="82" href="#82">82</a><span class="c">/* SPLAY_ROTATE_{LEFT,RIGHT} expect that tmp hold SPLAY_{RIGHT,LEFT} */</span>
<a class="l" name="83" href="#83">83</a>#<b>define</b> <a class="xm" name="SPLAY_ROTATE_RIGHT"/><a href="/s?refs=SPLAY_ROTATE_RIGHT&amp;project=OpenBSD" class="xm">SPLAY_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {           \
<a class="l" name="84" href="#84">84</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);  \
<a class="l" name="85" href="#85">85</a>    <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;         \
<a class="l" name="86" href="#86">86</a>    (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                     \
<a class="l" name="87" href="#87">87</a>} <b>while</b> (0)
<a class="l" name="88" href="#88">88</a>
<a class="l" name="89" href="#89">89</a>#<b>define</b> <a class="xm" name="SPLAY_ROTATE_LEFT"/><a href="/s?refs=SPLAY_ROTATE_LEFT&amp;project=OpenBSD" class="xm">SPLAY_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {            \
<a class="hl" name="90" href="#90">90</a>    <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);  \
<a class="l" name="91" href="#91">91</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;          \
<a class="l" name="92" href="#92">92</a>    (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                     \
<a class="l" name="93" href="#93">93</a>} <b>while</b> (0)
<a class="l" name="94" href="#94">94</a>
<a class="l" name="95" href="#95">95</a>#<b>define</b> <a class="xm" name="SPLAY_LINKLEFT"/><a href="/s?refs=SPLAY_LINKLEFT&amp;project=OpenBSD" class="xm">SPLAY_LINKLEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {               \
<a class="l" name="96" href="#96">96</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;          \
<a class="l" name="97" href="#97">97</a>    <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;                     \
<a class="l" name="98" href="#98">98</a>    (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);     \
<a class="l" name="99" href="#99">99</a>} <b>while</b> (0)
<a class="hl" name="100" href="#100">100</a>
<a class="l" name="101" href="#101">101</a>#<b>define</b> <a class="xm" name="SPLAY_LINKRIGHT"/><a href="/s?refs=SPLAY_LINKRIGHT&amp;project=OpenBSD" class="xm">SPLAY_LINKRIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {              \
<a class="l" name="102" href="#102">102</a>    <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;         \
<a class="l" name="103" href="#103">103</a>    <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;                     \
<a class="l" name="104" href="#104">104</a>    (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="l" name="105" href="#105">105</a>} <b>while</b> (0)
<a class="l" name="106" href="#106">106</a>
<a class="l" name="107" href="#107">107</a>#<b>define</b> <a class="xm" name="SPLAY_ASSEMBLE"/><a href="/s?refs=SPLAY_ASSEMBLE&amp;project=OpenBSD" class="xm">SPLAY_ASSEMBLE</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=node&amp;project=OpenBSD">node</a>, <a href="/s?defs=left&amp;project=OpenBSD">left</a>, <a href="/s?defs=right&amp;project=OpenBSD">right</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {     \
<a class="l" name="108" href="#108">108</a>    <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=left&amp;project=OpenBSD">left</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>); \
<a class="l" name="109" href="#109">109</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=right&amp;project=OpenBSD">right</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="hl" name="110" href="#110">110</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=node&amp;project=OpenBSD">node</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>); \
<a class="l" name="111" href="#111">111</a>    <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=node&amp;project=OpenBSD">node</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>); \
<a class="l" name="112" href="#112">112</a>} <b>while</b> (0)
<a class="l" name="113" href="#113">113</a>
<a class="l" name="114" href="#114">114</a><span class="c">/* Generates prototypes and inline functions */</span>
<a class="l" name="115" href="#115">115</a>
<a class="l" name="116" href="#116">116</a>#<b>define</b> <a class="xm" name="SPLAY_PROTOTYPE"/><a href="/s?refs=SPLAY_PROTOTYPE&amp;project=OpenBSD" class="xm">SPLAY_PROTOTYPE</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)             \
<a class="l" name="117" href="#117">117</a><b>void</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);            \
<a class="l" name="118" href="#118">118</a><b>void</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_MINMAX&amp;project=OpenBSD">_SPLAY_MINMAX</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>int</b>);               \
<a class="l" name="119" href="#119">119</a><b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_INSERT&amp;project=OpenBSD">_SPLAY_INSERT</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);     \
<a class="hl" name="120" href="#120">120</a><b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_REMOVE&amp;project=OpenBSD">_SPLAY_REMOVE</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);     \
<a class="l" name="121" href="#121">121</a>                                    \
<a class="l" name="122" href="#122">122</a><span class="c">/* Finds the node with the same key as elm */</span>               \
<a class="l" name="123" href="#123">123</a><b>static</b> <a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <a href="/s?defs=__inline&amp;project=OpenBSD">__inline</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                  \
<a class="l" name="124" href="#124">124</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_FIND&amp;project=OpenBSD">_SPLAY_FIND</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)          \
<a class="l" name="125" href="#125">125</a>{                                   \
<a class="l" name="126" href="#126">126</a>    <b>if</b> (<a class="d" href="#SPLAY_EMPTY">SPLAY_EMPTY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>))                      \
<a class="l" name="127" href="#127">127</a>        <b>return</b>(<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                       \
<a class="l" name="128" href="#128">128</a>    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                    \
<a class="l" name="129" href="#129">129</a>    <b>if</b> ((<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>) == 0)              \
<a class="hl" name="130" href="#130">130</a>        <b>return</b> (<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>);                \
<a class="l" name="131" href="#131">131</a>    <b>return</b> (<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                          \
<a class="l" name="132" href="#132">132</a>}                                   \
<a class="l" name="133" href="#133">133</a>                                    \
<a class="l" name="134" href="#134">134</a><b>static</b> <a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <a href="/s?defs=__inline&amp;project=OpenBSD">__inline</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                  \
<a class="l" name="135" href="#135">135</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_NEXT&amp;project=OpenBSD">_SPLAY_NEXT</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)          \
<a class="l" name="136" href="#136">136</a>{                                   \
<a class="l" name="137" href="#137">137</a>    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                    \
<a class="l" name="138" href="#138">138</a>    <b>if</b> (<a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>) {              \
<a class="l" name="139" href="#139">139</a>        <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);              \
<a class="hl" name="140" href="#140">140</a>        <b>while</b> (<a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>) {        \
<a class="l" name="141" href="#141">141</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);           \
<a class="l" name="142" href="#142">142</a>        }                           \
<a class="l" name="143" href="#143">143</a>    } <b>else</b>                              \
<a class="l" name="144" href="#144">144</a>        <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                     \
<a class="l" name="145" href="#145">145</a>    <b>return</b> (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                           \
<a class="l" name="146" href="#146">146</a>}                                   \
<a class="l" name="147" href="#147">147</a>                                    \
<a class="l" name="148" href="#148">148</a><b>static</b> <a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <a href="/s?defs=__inline&amp;project=OpenBSD">__inline</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                  \
<a class="l" name="149" href="#149">149</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_MIN_MAX&amp;project=OpenBSD">_SPLAY_MIN_MAX</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>int</b> <a href="/s?defs=val&amp;project=OpenBSD">val</a>)            \
<a class="hl" name="150" href="#150">150</a>{                                   \
<a class="l" name="151" href="#151">151</a>    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_MINMAX&amp;project=OpenBSD">_SPLAY_MINMAX</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=val&amp;project=OpenBSD">val</a>);                 \
<a class="l" name="152" href="#152">152</a>        <b>return</b> (<a class="d" href="#SPLAY_ROOT">SPLAY_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>));                  \
<a class="l" name="153" href="#153">153</a>}
<a class="l" name="154" href="#154">154</a>
<a class="l" name="155" href="#155">155</a><span class="c">/* Main splay operation.
<a class="l" name="156" href="#156">156</a> * Moves node close to the key of elm to top
<a class="l" name="157" href="#157">157</a> */</span>
<a class="l" name="158" href="#158">158</a>#<b>define</b> <a class="xm" name="SPLAY_GENERATE"/><a href="/s?refs=SPLAY_GENERATE&amp;project=OpenBSD" class="xm">SPLAY_GENERATE</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)              \
<a class="l" name="159" href="#159">159</a><b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                               \
<a class="hl" name="160" href="#160">160</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_INSERT&amp;project=OpenBSD">_SPLAY_INSERT</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)        \
<a class="l" name="161" href="#161">161</a>{                                   \
<a class="l" name="162" href="#162">162</a>    <b>if</b> (<a class="d" href="#SPLAY_EMPTY">SPLAY_EMPTY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>)) {                        \
<a class="l" name="163" href="#163">163</a>        <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;    \
<a class="l" name="164" href="#164">164</a>    } <b>else</b> {                                \
<a class="l" name="165" href="#165">165</a>        <b>int</b> <a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a>;                         \
<a class="l" name="166" href="#166">166</a>        <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                    \
<a class="l" name="167" href="#167">167</a>        <a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> = (<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>);          \
<a class="l" name="168" href="#168">168</a>        <b>if</b>(<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &lt; 0) {                        \
<a class="l" name="169" href="#169">169</a>            <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="hl" name="170" href="#170">170</a>            <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;     \
<a class="l" name="171" href="#171">171</a>            <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;     \
<a class="l" name="172" href="#172">172</a>        } <b>else</b> <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &gt; 0) {                    \
<a class="l" name="173" href="#173">173</a>            <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="174" href="#174">174</a>            <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>;      \
<a class="l" name="175" href="#175">175</a>            <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;    \
<a class="l" name="176" href="#176">176</a>        } <b>else</b>                          \
<a class="l" name="177" href="#177">177</a>            <b>return</b> ((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>);              \
<a class="l" name="178" href="#178">178</a>    }                                   \
<a class="l" name="179" href="#179">179</a>    (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                       \
<a class="hl" name="180" href="#180">180</a>    <b>return</b> (<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                          \
<a class="l" name="181" href="#181">181</a>}                                   \
<a class="l" name="182" href="#182">182</a>                                    \
<a class="l" name="183" href="#183">183</a><b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                               \
<a class="l" name="184" href="#184">184</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_REMOVE&amp;project=OpenBSD">_SPLAY_REMOVE</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)        \
<a class="l" name="185" href="#185">185</a>{                                   \
<a class="l" name="186" href="#186">186</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>;                     \
<a class="l" name="187" href="#187">187</a>    <b>if</b> (<a class="d" href="#SPLAY_EMPTY">SPLAY_EMPTY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>))                      \
<a class="l" name="188" href="#188">188</a>        <b>return</b> (<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                      \
<a class="l" name="189" href="#189">189</a>    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                    \
<a class="hl" name="190" href="#190">190</a>    <b>if</b> ((<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>) == 0) {            \
<a class="l" name="191" href="#191">191</a>        <b>if</b> (<a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>) {  \
<a class="l" name="192" href="#192">192</a>            (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="193" href="#193">193</a>        } <b>else</b> {                        \
<a class="l" name="194" href="#194">194</a>            <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);   \
<a class="l" name="195" href="#195">195</a>            (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a> = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="196" href="#196">196</a>            <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);            \
<a class="l" name="197" href="#197">197</a>            <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>;   \
<a class="l" name="198" href="#198">198</a>        }                           \
<a class="l" name="199" href="#199">199</a>        <b>return</b> (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                       \
<a class="hl" name="200" href="#200">200</a>    }                               \
<a class="l" name="201" href="#201">201</a>    <b>return</b> (<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                          \
<a class="l" name="202" href="#202">202</a>}                                   \
<a class="l" name="203" href="#203">203</a>                                    \
<a class="l" name="204" href="#204">204</a><b>void</b>                                    \
<a class="l" name="205" href="#205">205</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY&amp;project=OpenBSD">_SPLAY</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)           \
<a class="l" name="206" href="#206">206</a>{                                   \
<a class="l" name="207" href="#207">207</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> <a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, *<a href="/s?defs=__left&amp;project=OpenBSD">__left</a>, *<a href="/s?defs=__right&amp;project=OpenBSD">__right</a>, *<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>;          \
<a class="l" name="208" href="#208">208</a>    <b>int</b> <a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a>;                         \
<a class="l" name="209" href="#209">209</a>\
<a class="hl" name="210" href="#210">210</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(&amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(&amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;\
<a class="l" name="211" href="#211">211</a>    <a href="/s?defs=__left&amp;project=OpenBSD">__left</a> = <a href="/s?defs=__right&amp;project=OpenBSD">__right</a> = &amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>;                 \
<a class="l" name="212" href="#212">212</a>\
<a class="l" name="213" href="#213">213</a>    <b>while</b> ((<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> = (<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>))) {       \
<a class="l" name="214" href="#214">214</a>        <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &lt; 0) {                   \
<a class="l" name="215" href="#215">215</a>            <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="l" name="216" href="#216">216</a>            <b>if</b> (<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)              \
<a class="l" name="217" href="#217">217</a>                <b>break</b>;                  \
<a class="l" name="218" href="#218">218</a>            <b>if</b> ((<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>) &lt; 0){         \
<a class="l" name="219" href="#219">219</a>                <a class="d" href="#SPLAY_ROTATE_RIGHT">SPLAY_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>); \
<a class="hl" name="220" href="#220">220</a>                <b>if</b> (<a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)\
<a class="l" name="221" href="#221">221</a>                    <b>break</b>;              \
<a class="l" name="222" href="#222">222</a>            }                       \
<a class="l" name="223" href="#223">223</a>            <a class="d" href="#SPLAY_LINKLEFT">SPLAY_LINKLEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__right&amp;project=OpenBSD">__right</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);       \
<a class="l" name="224" href="#224">224</a>        } <b>else</b> <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &gt; 0) {                \
<a class="l" name="225" href="#225">225</a>            <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);   \
<a class="l" name="226" href="#226">226</a>            <b>if</b> (<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)              \
<a class="l" name="227" href="#227">227</a>                <b>break</b>;                  \
<a class="l" name="228" href="#228">228</a>            <b>if</b> ((<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>) &gt; 0){         \
<a class="l" name="229" href="#229">229</a>                <a class="d" href="#SPLAY_ROTATE_LEFT">SPLAY_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);  \
<a class="hl" name="230" href="#230">230</a>                <b>if</b> (<a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)\
<a class="l" name="231" href="#231">231</a>                    <b>break</b>;              \
<a class="l" name="232" href="#232">232</a>            }                       \
<a class="l" name="233" href="#233">233</a>            <a class="d" href="#SPLAY_LINKRIGHT">SPLAY_LINKRIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__left&amp;project=OpenBSD">__left</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);       \
<a class="l" name="234" href="#234">234</a>        }                           \
<a class="l" name="235" href="#235">235</a>    }                               \
<a class="l" name="236" href="#236">236</a>    <a class="d" href="#SPLAY_ASSEMBLE">SPLAY_ASSEMBLE</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, &amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, <a href="/s?defs=__left&amp;project=OpenBSD">__left</a>, <a href="/s?defs=__right&amp;project=OpenBSD">__right</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);      \
<a class="l" name="237" href="#237">237</a>}                                   \
<a class="l" name="238" href="#238">238</a>                                    \
<a class="l" name="239" href="#239">239</a><span class="c">/* Splay with either the minimum or the maximum element         \
<a class="hl" name="240" href="#240">240</a> * Used to find minimum or maximum element in tree.         \
<a class="l" name="241" href="#241">241</a> */</span>                                 \
<a class="l" name="242" href="#242">242</a><b>void</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_MINMAX&amp;project=OpenBSD">_SPLAY_MINMAX</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>int</b> <a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a>) \
<a class="l" name="243" href="#243">243</a>{                                   \
<a class="l" name="244" href="#244">244</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> <a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, *<a href="/s?defs=__left&amp;project=OpenBSD">__left</a>, *<a href="/s?defs=__right&amp;project=OpenBSD">__right</a>, *<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>;          \
<a class="l" name="245" href="#245">245</a>\
<a class="l" name="246" href="#246">246</a>    <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>(&amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>(&amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;\
<a class="l" name="247" href="#247">247</a>    <a href="/s?defs=__left&amp;project=OpenBSD">__left</a> = <a href="/s?defs=__right&amp;project=OpenBSD">__right</a> = &amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>;                 \
<a class="l" name="248" href="#248">248</a>\
<a class="l" name="249" href="#249">249</a>    <b>while</b> (<span class="n">1</span>) {                         \
<a class="hl" name="250" href="#250">250</a>        <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &lt; 0) {                   \
<a class="l" name="251" href="#251">251</a>            <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> = <a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="l" name="252" href="#252">252</a>            <b>if</b> (<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)              \
<a class="l" name="253" href="#253">253</a>                <b>break</b>;                  \
<a class="l" name="254" href="#254">254</a>            <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &lt; 0){                \
<a class="l" name="255" href="#255">255</a>                <a class="d" href="#SPLAY_ROTATE_RIGHT">SPLAY_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>); \
<a class="l" name="256" href="#256">256</a>                <b>if</b> (<a class="d" href="#SPLAY_LEFT">SPLAY_LEFT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)\
<a class="l" name="257" href="#257">257</a>                    <b>break</b>;              \
<a class="l" name="258" href="#258">258</a>            }                       \
<a class="l" name="259" href="#259">259</a>            <a class="d" href="#SPLAY_LINKLEFT">SPLAY_LINKLEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__right&amp;project=OpenBSD">__right</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);       \
<a class="hl" name="260" href="#260">260</a>        } <b>else</b> <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &gt; 0) {                \
<a class="l" name="261" href="#261">261</a>            <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> = <a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);   \
<a class="l" name="262" href="#262">262</a>            <b>if</b> (<a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a> == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)              \
<a class="l" name="263" href="#263">263</a>                <b>break</b>;                  \
<a class="l" name="264" href="#264">264</a>            <b>if</b> (<a href="/s?defs=__comp&amp;project=OpenBSD">__comp</a> &gt; 0) {               \
<a class="l" name="265" href="#265">265</a>                <a class="d" href="#SPLAY_ROTATE_LEFT">SPLAY_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__tmp&amp;project=OpenBSD">__tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);  \
<a class="l" name="266" href="#266">266</a>                <b>if</b> (<a class="d" href="#SPLAY_RIGHT">SPLAY_RIGHT</a>((<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=sph_root&amp;project=OpenBSD">sph_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)\
<a class="l" name="267" href="#267">267</a>                    <b>break</b>;              \
<a class="l" name="268" href="#268">268</a>            }                       \
<a class="l" name="269" href="#269">269</a>            <a class="d" href="#SPLAY_LINKRIGHT">SPLAY_LINKRIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=__left&amp;project=OpenBSD">__left</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);       \
<a class="hl" name="270" href="#270">270</a>        }                           \
<a class="l" name="271" href="#271">271</a>    }                               \
<a class="l" name="272" href="#272">272</a>    <a class="d" href="#SPLAY_ASSEMBLE">SPLAY_ASSEMBLE</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, &amp;<a href="/s?defs=__node&amp;project=OpenBSD">__node</a>, <a href="/s?defs=__left&amp;project=OpenBSD">__left</a>, <a href="/s?defs=__right&amp;project=OpenBSD">__right</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);      \
<a class="l" name="273" href="#273">273</a>}
<a class="l" name="274" href="#274">274</a>
<a class="l" name="275" href="#275">275</a>#<b>define</b> <a class="xm" name="SPLAY_NEGINF"/><a href="/s?refs=SPLAY_NEGINF&amp;project=OpenBSD" class="xm">SPLAY_NEGINF</a>    -<span class="n">1</span>
<a class="l" name="276" href="#276">276</a>#<b>define</b> <a class="xm" name="SPLAY_INF"/><a href="/s?refs=SPLAY_INF&amp;project=OpenBSD" class="xm">SPLAY_INF</a>   <span class="n">1</span>
<a class="l" name="277" href="#277">277</a>
<a class="l" name="278" href="#278">278</a>#<b>define</b> <a class="xm" name="SPLAY_INSERT"/><a href="/s?refs=SPLAY_INSERT&amp;project=OpenBSD" class="xm">SPLAY_INSERT</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_INSERT&amp;project=OpenBSD">_SPLAY_INSERT</a>(x, y)
<a class="l" name="279" href="#279">279</a>#<b>define</b> <a class="xm" name="SPLAY_REMOVE"/><a href="/s?refs=SPLAY_REMOVE&amp;project=OpenBSD" class="xm">SPLAY_REMOVE</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_REMOVE&amp;project=OpenBSD">_SPLAY_REMOVE</a>(x, y)
<a class="hl" name="280" href="#280">280</a>#<b>define</b> <a class="xm" name="SPLAY_FIND"/><a href="/s?refs=SPLAY_FIND&amp;project=OpenBSD" class="xm">SPLAY_FIND</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)      <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_FIND&amp;project=OpenBSD">_SPLAY_FIND</a>(x, y)
<a class="l" name="281" href="#281">281</a>#<b>define</b> <a class="xm" name="SPLAY_NEXT"/><a href="/s?refs=SPLAY_NEXT&amp;project=OpenBSD" class="xm">SPLAY_NEXT</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)      <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_NEXT&amp;project=OpenBSD">_SPLAY_NEXT</a>(x, y)
<a class="l" name="282" href="#282">282</a>#<b>define</b> <a class="xm" name="SPLAY_MIN"/><a href="/s?refs=SPLAY_MIN&amp;project=OpenBSD" class="xm">SPLAY_MIN</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x)      (<a class="d" href="#SPLAY_EMPTY">SPLAY_EMPTY</a>(x) ? <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>  \
<a class="l" name="283" href="#283">283</a>                    : <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_MIN_MAX&amp;project=OpenBSD">_SPLAY_MIN_MAX</a>(x, <a class="d" href="#SPLAY_NEGINF">SPLAY_NEGINF</a>))
<a class="l" name="284" href="#284">284</a>#<b>define</b> <a class="xm" name="SPLAY_MAX"/><a href="/s?refs=SPLAY_MAX&amp;project=OpenBSD" class="xm">SPLAY_MAX</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x)      (<a class="d" href="#SPLAY_EMPTY">SPLAY_EMPTY</a>(x) ? <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>  \
<a class="l" name="285" href="#285">285</a>                    : <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_SPLAY_MIN_MAX&amp;project=OpenBSD">_SPLAY_MIN_MAX</a>(x, <a class="d" href="#SPLAY_INF">SPLAY_INF</a>))
<a class="l" name="286" href="#286">286</a>
<a class="l" name="287" href="#287">287</a>#<b>define</b> <a class="xm" name="SPLAY_FOREACH"/><a href="/s?refs=SPLAY_FOREACH&amp;project=OpenBSD" class="xm">SPLAY_FOREACH</a>(x, <a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>)                    \
<a class="l" name="288" href="#288">288</a>    <b>for</b> ((x) = <a class="d" href="#SPLAY_MIN">SPLAY_MIN</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>);               \
<a class="l" name="289" href="#289">289</a>         (x) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                       \
<a class="hl" name="290" href="#290">290</a>         (x) = <a class="d" href="#SPLAY_NEXT">SPLAY_NEXT</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>, x))
<a class="l" name="291" href="#291">291</a>
<a class="l" name="292" href="#292">292</a><span class="c">/* Macros that define a red-black tree */</span>
<a class="l" name="293" href="#293">293</a>#<b>define</b> <a class="xm" name="RB_HEAD"/><a href="/s?refs=RB_HEAD&amp;project=OpenBSD" class="xm">RB_HEAD</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>)                     \
<a class="l" name="294" href="#294">294</a><b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> {                               \
<a class="l" name="295" href="#295">295</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>; <span class="c">/* root of the tree */</span>           \
<a class="l" name="296" href="#296">296</a>}
<a class="l" name="297" href="#297">297</a>
<a class="l" name="298" href="#298">298</a>#<b>define</b> <a class="xm" name="RB_INITIALIZER"/><a href="/s?refs=RB_INITIALIZER&amp;project=OpenBSD" class="xm">RB_INITIALIZER</a>(<a href="/s?defs=root&amp;project=OpenBSD">root</a>)                        \
<a class="l" name="299" href="#299">299</a>    { <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> }
<a class="hl" name="300" href="#300">300</a>
<a class="l" name="301" href="#301">301</a>#<b>define</b> <a class="xm" name="RB_INIT"/><a href="/s?refs=RB_INIT&amp;project=OpenBSD" class="xm">RB_INIT</a>(<a href="/s?defs=root&amp;project=OpenBSD">root</a>) <b>do</b> {                      \
<a class="l" name="302" href="#302">302</a>    (<a href="/s?defs=root&amp;project=OpenBSD">root</a>)-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                    \
<a class="l" name="303" href="#303">303</a>} <b>while</b> (0)
<a class="l" name="304" href="#304">304</a>
<a class="l" name="305" href="#305">305</a>#<b>define</b> <a class="xm" name="RB_BLACK"/><a href="/s?refs=RB_BLACK&amp;project=OpenBSD" class="xm">RB_BLACK</a>    0
<a class="l" name="306" href="#306">306</a>#<b>define</b> <a class="xm" name="RB_RED"/><a href="/s?refs=RB_RED&amp;project=OpenBSD" class="xm">RB_RED</a>      <span class="n">1</span>
<a class="l" name="307" href="#307">307</a>#<b>define</b> <a class="xm" name="RB_ENTRY"/><a href="/s?refs=RB_ENTRY&amp;project=OpenBSD" class="xm">RB_ENTRY</a>(<a href="/s?defs=type&amp;project=OpenBSD">type</a>)                          \
<a class="l" name="308" href="#308">308</a><b>struct</b> {                                \
<a class="l" name="309" href="#309">309</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=rbe_left&amp;project=OpenBSD">rbe_left</a>;      <span class="c">/* left element */</span>      \
<a class="hl" name="310" href="#310">310</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=rbe_right&amp;project=OpenBSD">rbe_right</a>;     <span class="c">/* right element */</span>     \
<a class="l" name="311" href="#311">311</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=rbe_parent&amp;project=OpenBSD">rbe_parent</a>;    <span class="c">/* parent element */</span>        \
<a class="l" name="312" href="#312">312</a>    <b>int</b> <a href="/s?defs=rbe_color&amp;project=OpenBSD">rbe_color</a>;          <span class="c">/* node color */</span>        \
<a class="l" name="313" href="#313">313</a>}
<a class="l" name="314" href="#314">314</a>
<a class="l" name="315" href="#315">315</a>#<b>define</b> <a class="xm" name="RB_LEFT"/><a href="/s?refs=RB_LEFT&amp;project=OpenBSD" class="xm">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)     (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>.<a href="/s?defs=rbe_left&amp;project=OpenBSD">rbe_left</a>
<a class="l" name="316" href="#316">316</a>#<b>define</b> <a class="xm" name="RB_RIGHT"/><a href="/s?refs=RB_RIGHT&amp;project=OpenBSD" class="xm">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)        (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>.<a href="/s?defs=rbe_right&amp;project=OpenBSD">rbe_right</a>
<a class="l" name="317" href="#317">317</a>#<b>define</b> <a class="xm" name="RB_PARENT"/><a href="/s?refs=RB_PARENT&amp;project=OpenBSD" class="xm">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)       (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>.<a href="/s?defs=rbe_parent&amp;project=OpenBSD">rbe_parent</a>
<a class="l" name="318" href="#318">318</a>#<b>define</b> <a class="xm" name="RB_COLOR"/><a href="/s?refs=RB_COLOR&amp;project=OpenBSD" class="xm">RB_COLOR</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)        (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>.<a href="/s?defs=rbe_color&amp;project=OpenBSD">rbe_color</a>
<a class="l" name="319" href="#319">319</a>#<b>define</b> <a class="xm" name="RB_ROOT"/><a href="/s?refs=RB_ROOT&amp;project=OpenBSD" class="xm">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>)           (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>
<a class="hl" name="320" href="#320">320</a>#<b>define</b> <a class="xm" name="RB_EMPTY"/><a href="/s?refs=RB_EMPTY&amp;project=OpenBSD" class="xm">RB_EMPTY</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>)          (<a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)
<a class="l" name="321" href="#321">321</a>
<a class="l" name="322" href="#322">322</a>#<b>define</b> <a class="xm" name="RB_SET"/><a href="/s?refs=RB_SET&amp;project=OpenBSD" class="xm">RB_SET</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {                 \
<a class="l" name="323" href="#323">323</a>    <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;                 \
<a class="l" name="324" href="#324">324</a>    <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;      \
<a class="l" name="325" href="#325">325</a>    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RED">RB_RED</a>;                  \
<a class="l" name="326" href="#326">326</a>} <b>while</b> (0)
<a class="l" name="327" href="#327">327</a>
<a class="l" name="328" href="#328">328</a>#<b>define</b> <a class="xm" name="RB_SET_BLACKRED"/><a href="/s?refs=RB_SET_BLACKRED&amp;project=OpenBSD" class="xm">RB_SET_BLACKRED</a>(<a href="/s?defs=black&amp;project=OpenBSD">black</a>, <a href="/s?defs=red&amp;project=OpenBSD">red</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {             \
<a class="l" name="329" href="#329">329</a>    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=black&amp;project=OpenBSD">black</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;              \
<a class="hl" name="330" href="#330">330</a>    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=red&amp;project=OpenBSD">red</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RED">RB_RED</a>;                  \
<a class="l" name="331" href="#331">331</a>} <b>while</b> (0)
<a class="l" name="332" href="#332">332</a>
<a class="l" name="333" href="#333">333</a>#<b>ifndef</b> <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>
<a class="l" name="334" href="#334">334</a>#<b>define</b> <a class="xm" name="RB_AUGMENT"/><a href="/s?refs=RB_AUGMENT&amp;project=OpenBSD" class="xm">RB_AUGMENT</a>(x)   <b>do</b> {} <b>while</b> (0)
<a class="l" name="335" href="#335">335</a>#<b>endif</b>
<a class="l" name="336" href="#336">336</a>
<a class="l" name="337" href="#337">337</a>#<b>define</b> <a class="xm" name="RB_ROTATE_LEFT"/><a href="/s?refs=RB_ROTATE_LEFT&amp;project=OpenBSD" class="xm">RB_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {          \
<a class="l" name="338" href="#338">338</a>    (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>) = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);                   \
<a class="l" name="339" href="#339">339</a>    <b>if</b> ((<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))) {     \
<a class="hl" name="340" href="#340">340</a>        <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);      \
<a class="l" name="341" href="#341">341</a>    }                               \
<a class="l" name="342" href="#342">342</a>    <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                        \
<a class="l" name="343" href="#343">343</a>    <b>if</b> ((<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))) {      \
<a class="l" name="344" href="#344">344</a>        <b>if</b> ((<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>) == <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) \
<a class="l" name="345" href="#345">345</a>            <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);  \
<a class="l" name="346" href="#346">346</a>        <b>else</b>                            \
<a class="l" name="347" href="#347">347</a>            <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>); \
<a class="l" name="348" href="#348">348</a>    } <b>else</b>                              \
<a class="l" name="349" href="#349">349</a>        (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a> = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);               \
<a class="hl" name="350" href="#350">350</a>    <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                    \
<a class="l" name="351" href="#351">351</a>    <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                  \
<a class="l" name="352" href="#352">352</a>    <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                        \
<a class="l" name="353" href="#353">353</a>    <b>if</b> ((<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))                    \
<a class="l" name="354" href="#354">354</a>        <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>));          \
<a class="l" name="355" href="#355">355</a>} <b>while</b> (0)
<a class="l" name="356" href="#356">356</a>
<a class="l" name="357" href="#357">357</a>#<b>define</b> <a class="xm" name="RB_ROTATE_RIGHT"/><a href="/s?refs=RB_ROTATE_RIGHT&amp;project=OpenBSD" class="xm">RB_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) <b>do</b> {         \
<a class="l" name="358" href="#358">358</a>    (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>) = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);                    \
<a class="l" name="359" href="#359">359</a>    <b>if</b> ((<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))) {     \
<a class="hl" name="360" href="#360">360</a>        <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);     \
<a class="l" name="361" href="#361">361</a>    }                               \
<a class="l" name="362" href="#362">362</a>    <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                        \
<a class="l" name="363" href="#363">363</a>    <b>if</b> ((<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))) {      \
<a class="l" name="364" href="#364">364</a>        <b>if</b> ((<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>) == <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) \
<a class="l" name="365" href="#365">365</a>            <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);  \
<a class="l" name="366" href="#366">366</a>        <b>else</b>                            \
<a class="l" name="367" href="#367">367</a>            <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>); \
<a class="l" name="368" href="#368">368</a>    } <b>else</b>                              \
<a class="l" name="369" href="#369">369</a>        (<a href="/s?defs=head&amp;project=OpenBSD">head</a>)-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a> = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);               \
<a class="hl" name="370" href="#370">370</a>    <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                   \
<a class="l" name="371" href="#371">371</a>    <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                  \
<a class="l" name="372" href="#372">372</a>    <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                        \
<a class="l" name="373" href="#373">373</a>    <b>if</b> ((<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))                    \
<a class="l" name="374" href="#374">374</a>        <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>));          \
<a class="l" name="375" href="#375">375</a>} <b>while</b> (0)
<a class="l" name="376" href="#376">376</a>
<a class="l" name="377" href="#377">377</a><span class="c">/* Generates prototypes and inline functions */</span>
<a class="l" name="378" href="#378">378</a>#<b>define</b> <a class="xm" name="RB_PROTOTYPE"/><a href="/s?refs=RB_PROTOTYPE&amp;project=OpenBSD" class="xm">RB_PROTOTYPE</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)                \
<a class="l" name="379" href="#379">379</a>    <a class="d" href="#RB_PROTOTYPE_INTERNAL">RB_PROTOTYPE_INTERNAL</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>,)
<a class="hl" name="380" href="#380">380</a>#<b>define</b> <a class="xm" name="RB_PROTOTYPE_STATIC"/><a href="/s?refs=RB_PROTOTYPE_STATIC&amp;project=OpenBSD" class="xm">RB_PROTOTYPE_STATIC</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)         \
<a class="l" name="381" href="#381">381</a>    <a class="d" href="#RB_PROTOTYPE_INTERNAL">RB_PROTOTYPE_INTERNAL</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>, <a href="/s?defs=__attribute__&amp;project=OpenBSD">__attribute__</a>((<a href="/s?defs=__unused__&amp;project=OpenBSD">__unused__</a>)) <b>static</b>)
<a class="l" name="382" href="#382">382</a>#<b>define</b> <a class="xm" name="RB_PROTOTYPE_INTERNAL"/><a href="/s?refs=RB_PROTOTYPE_INTERNAL&amp;project=OpenBSD" class="xm">RB_PROTOTYPE_INTERNAL</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>, <a href="/s?defs=attr&amp;project=OpenBSD">attr</a>)     \
<a class="l" name="383" href="#383">383</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>void</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_INSERT_COLOR&amp;project=OpenBSD">_RB_INSERT_COLOR</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);     \
<a class="l" name="384" href="#384">384</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>void</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_REMOVE_COLOR&amp;project=OpenBSD">_RB_REMOVE_COLOR</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);\
<a class="l" name="385" href="#385">385</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_REMOVE&amp;project=OpenBSD">_RB_REMOVE</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);   \
<a class="l" name="386" href="#386">386</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_INSERT&amp;project=OpenBSD">_RB_INSERT</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);   \
<a class="l" name="387" href="#387">387</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_FIND&amp;project=OpenBSD">_RB_FIND</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);     \
<a class="l" name="388" href="#388">388</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NFIND&amp;project=OpenBSD">_RB_NFIND</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);    \
<a class="l" name="389" href="#389">389</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NEXT&amp;project=OpenBSD">_RB_NEXT</a>(<b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);            \
<a class="hl" name="390" href="#390">390</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_PREV&amp;project=OpenBSD">_RB_PREV</a>(<b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *);            \
<a class="l" name="391" href="#391">391</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_MINMAX&amp;project=OpenBSD">_RB_MINMAX</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *, <b>int</b>);         \
<a class="l" name="392" href="#392">392</a>                                    \
<a class="l" name="393" href="#393">393</a>
<a class="l" name="394" href="#394">394</a><span class="c">/* Main rb operation.
<a class="l" name="395" href="#395">395</a> * Moves node close to the key of elm to top
<a class="l" name="396" href="#396">396</a> */</span>
<a class="l" name="397" href="#397">397</a>#<b>define</b> <a class="xm" name="RB_GENERATE"/><a href="/s?refs=RB_GENERATE&amp;project=OpenBSD" class="xm">RB_GENERATE</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)             \
<a class="l" name="398" href="#398">398</a>    <a class="d" href="#RB_GENERATE_INTERNAL">RB_GENERATE_INTERNAL</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>,)
<a class="l" name="399" href="#399">399</a>#<b>define</b> <a class="xm" name="RB_GENERATE_STATIC"/><a href="/s?refs=RB_GENERATE_STATIC&amp;project=OpenBSD" class="xm">RB_GENERATE_STATIC</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)          \
<a class="hl" name="400" href="#400">400</a>    <a class="d" href="#RB_GENERATE_INTERNAL">RB_GENERATE_INTERNAL</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>, <a href="/s?defs=__attribute__&amp;project=OpenBSD">__attribute__</a>((<a href="/s?defs=__unused__&amp;project=OpenBSD">__unused__</a>)) <b>static</b>)
<a class="l" name="401" href="#401">401</a>#<b>define</b> <a class="xm" name="RB_GENERATE_INTERNAL"/><a href="/s?refs=RB_GENERATE_INTERNAL&amp;project=OpenBSD" class="xm">RB_GENERATE_INTERNAL</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=type&amp;project=OpenBSD">type</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>, <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>, <a href="/s?defs=attr&amp;project=OpenBSD">attr</a>)      \
<a class="l" name="402" href="#402">402</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>void</b>                               \
<a class="l" name="403" href="#403">403</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_INSERT_COLOR&amp;project=OpenBSD">_RB_INSERT_COLOR</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)     \
<a class="l" name="404" href="#404">404</a>{                                   \
<a class="l" name="405" href="#405">405</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, *<a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, *<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                \
<a class="l" name="406" href="#406">406</a>    <b>while</b> ((<a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) &amp;&amp;          \
<a class="l" name="407" href="#407">407</a>        <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_RED">RB_RED</a>) {            \
<a class="l" name="408" href="#408">408</a>        <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="409" href="#409">409</a>        <b>if</b> (<a href="/s?defs=parent&amp;project=OpenBSD">parent</a> == <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) {        \
<a class="hl" name="410" href="#410">410</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="411" href="#411">411</a>            <b>if</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> &amp;&amp; <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_RED">RB_RED</a>) {    \
<a class="l" name="412" href="#412">412</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;    \
<a class="l" name="413" href="#413">413</a>                <a class="d" href="#RB_SET_BLACKRED">RB_SET_BLACKRED</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="414" href="#414">414</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>;              \
<a class="l" name="415" href="#415">415</a>                <b>continue</b>;               \
<a class="l" name="416" href="#416">416</a>            }                       \
<a class="l" name="417" href="#417">417</a>            <b>if</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>) {       \
<a class="l" name="418" href="#418">418</a>                <a class="d" href="#RB_ROTATE_LEFT">RB_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="419" href="#419">419</a>                <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;               \
<a class="hl" name="420" href="#420">420</a>                <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;               \
<a class="l" name="421" href="#421">421</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;              \
<a class="l" name="422" href="#422">422</a>            }                       \
<a class="l" name="423" href="#423">423</a>            <a class="d" href="#RB_SET_BLACKRED">RB_SET_BLACKRED</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="l" name="424" href="#424">424</a>            <a class="d" href="#RB_ROTATE_RIGHT">RB_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>); \
<a class="l" name="425" href="#425">425</a>        } <b>else</b> {                        \
<a class="l" name="426" href="#426">426</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="l" name="427" href="#427">427</a>            <b>if</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> &amp;&amp; <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_RED">RB_RED</a>) {    \
<a class="l" name="428" href="#428">428</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;    \
<a class="l" name="429" href="#429">429</a>                <a class="d" href="#RB_SET_BLACKRED">RB_SET_BLACKRED</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="hl" name="430" href="#430">430</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>;              \
<a class="l" name="431" href="#431">431</a>                <b>continue</b>;               \
<a class="l" name="432" href="#432">432</a>            }                       \
<a class="l" name="433" href="#433">433</a>            <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>) {        \
<a class="l" name="434" href="#434">434</a>                <a class="d" href="#RB_ROTATE_RIGHT">RB_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="435" href="#435">435</a>                <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;               \
<a class="l" name="436" href="#436">436</a>                <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;               \
<a class="l" name="437" href="#437">437</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;              \
<a class="l" name="438" href="#438">438</a>            }                       \
<a class="l" name="439" href="#439">439</a>            <a class="d" href="#RB_SET_BLACKRED">RB_SET_BLACKRED</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="hl" name="440" href="#440">440</a>            <a class="d" href="#RB_ROTATE_LEFT">RB_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=gparent&amp;project=OpenBSD">gparent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);  \
<a class="l" name="441" href="#441">441</a>        }                           \
<a class="l" name="442" href="#442">442</a>    }                               \
<a class="l" name="443" href="#443">443</a>    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;         \
<a class="l" name="444" href="#444">444</a>}                                   \
<a class="l" name="445" href="#445">445</a>                                    \
<a class="l" name="446" href="#446">446</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>void</b>                               \
<a class="l" name="447" href="#447">447</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_REMOVE_COLOR&amp;project=OpenBSD">_RB_REMOVE_COLOR</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>) \
<a class="l" name="448" href="#448">448</a>{                                   \
<a class="l" name="449" href="#449">449</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                       \
<a class="hl" name="450" href="#450">450</a>    <b>while</b> ((<a href="/s?defs=elm&amp;project=OpenBSD">elm</a> == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> || <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>) &amp;&amp; \
<a class="l" name="451" href="#451">451</a>        <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> != <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>)) {                 \
<a class="l" name="452" href="#452">452</a>        <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>) {            \
<a class="l" name="453" href="#453">453</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="l" name="454" href="#454">454</a>            <b>if</b> (<a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_RED">RB_RED</a>) {       \
<a class="l" name="455" href="#455">455</a>                <a class="d" href="#RB_SET_BLACKRED">RB_SET_BLACKRED</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="l" name="456" href="#456">456</a>                <a class="d" href="#RB_ROTATE_LEFT">RB_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="457" href="#457">457</a>                <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);      \
<a class="l" name="458" href="#458">458</a>            }                       \
<a class="l" name="459" href="#459">459</a>            <b>if</b> ((<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> ||     \
<a class="hl" name="460" href="#460">460</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>) &amp;&amp;\
<a class="l" name="461" href="#461">461</a>                (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> ||        \
<a class="l" name="462" href="#462">462</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>)) {\
<a class="l" name="463" href="#463">463</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RED">RB_RED</a>;      \
<a class="l" name="464" href="#464">464</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;               \
<a class="l" name="465" href="#465">465</a>                <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);     \
<a class="l" name="466" href="#466">466</a>            } <b>else</b> {                    \
<a class="l" name="467" href="#467">467</a>                <b>if</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> || \
<a class="l" name="468" href="#468">468</a>                    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>) {\
<a class="l" name="469" href="#469">469</a>                    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=oleft&amp;project=OpenBSD">oleft</a>;     \
<a class="hl" name="470" href="#470">470</a>                    <b>if</b> ((<a href="/s?defs=oleft&amp;project=OpenBSD">oleft</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))\
<a class="l" name="471" href="#471">471</a>                        <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=oleft&amp;project=OpenBSD">oleft</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;\
<a class="l" name="472" href="#472">472</a>                    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RED">RB_RED</a>;  \
<a class="l" name="473" href="#473">473</a>                    <a class="d" href="#RB_ROTATE_RIGHT">RB_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=oleft&amp;project=OpenBSD">oleft</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="474" href="#474">474</a>                    <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);  \
<a class="l" name="475" href="#475">475</a>                }                   \
<a class="l" name="476" href="#476">476</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="477" href="#477">477</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>; \
<a class="l" name="478" href="#478">478</a>                <b>if</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))       \
<a class="l" name="479" href="#479">479</a>                    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;\
<a class="hl" name="480" href="#480">480</a>                <a class="d" href="#RB_ROTATE_LEFT">RB_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="481" href="#481">481</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>);            \
<a class="l" name="482" href="#482">482</a>                <b>break</b>;                  \
<a class="l" name="483" href="#483">483</a>            }                       \
<a class="l" name="484" href="#484">484</a>        } <b>else</b> {                        \
<a class="l" name="485" href="#485">485</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);           \
<a class="l" name="486" href="#486">486</a>            <b>if</b> (<a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_RED">RB_RED</a>) {       \
<a class="l" name="487" href="#487">487</a>                <a class="d" href="#RB_SET_BLACKRED">RB_SET_BLACKRED</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);    \
<a class="l" name="488" href="#488">488</a>                <a class="d" href="#RB_ROTATE_RIGHT">RB_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="489" href="#489">489</a>                <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);       \
<a class="hl" name="490" href="#490">490</a>            }                       \
<a class="l" name="491" href="#491">491</a>            <b>if</b> ((<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> ||     \
<a class="l" name="492" href="#492">492</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>) &amp;&amp;\
<a class="l" name="493" href="#493">493</a>                (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> ||        \
<a class="l" name="494" href="#494">494</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>)) {\
<a class="l" name="495" href="#495">495</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RED">RB_RED</a>;      \
<a class="l" name="496" href="#496">496</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;               \
<a class="l" name="497" href="#497">497</a>                <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);     \
<a class="l" name="498" href="#498">498</a>            } <b>else</b> {                    \
<a class="l" name="499" href="#499">499</a>                <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> ||  \
<a class="hl" name="500" href="#500">500</a>                    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a class="d" href="#RB_BLACK">RB_BLACK</a>) {\
<a class="l" name="501" href="#501">501</a>                    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=oright&amp;project=OpenBSD">oright</a>;        \
<a class="l" name="502" href="#502">502</a>                    <b>if</b> ((<a href="/s?defs=oright&amp;project=OpenBSD">oright</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))\
<a class="l" name="503" href="#503">503</a>                        <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=oright&amp;project=OpenBSD">oright</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;\
<a class="l" name="504" href="#504">504</a>                    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_RED">RB_RED</a>;  \
<a class="l" name="505" href="#505">505</a>                    <a class="d" href="#RB_ROTATE_LEFT">RB_ROTATE_LEFT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=oright&amp;project=OpenBSD">oright</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="506" href="#506">506</a>                    <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);   \
<a class="l" name="507" href="#507">507</a>                }                   \
<a class="l" name="508" href="#508">508</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="509" href="#509">509</a>                <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>; \
<a class="hl" name="510" href="#510">510</a>                <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))        \
<a class="l" name="511" href="#511">511</a>                    <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;\
<a class="l" name="512" href="#512">512</a>                <a class="d" href="#RB_ROTATE_RIGHT">RB_ROTATE_RIGHT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);\
<a class="l" name="513" href="#513">513</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>);            \
<a class="l" name="514" href="#514">514</a>                <b>break</b>;                  \
<a class="l" name="515" href="#515">515</a>            }                       \
<a class="l" name="516" href="#516">516</a>        }                           \
<a class="l" name="517" href="#517">517</a>    }                               \
<a class="l" name="518" href="#518">518</a>    <b>if</b> (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                            \
<a class="l" name="519" href="#519">519</a>        <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a class="d" href="#RB_BLACK">RB_BLACK</a>;            \
<a class="hl" name="520" href="#520">520</a>}                                   \
<a class="l" name="521" href="#521">521</a>                                    \
<a class="l" name="522" href="#522">522</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="l" name="523" href="#523">523</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_REMOVE&amp;project=OpenBSD">_RB_REMOVE</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)           \
<a class="l" name="524" href="#524">524</a>{                                   \
<a class="l" name="525" href="#525">525</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=child&amp;project=OpenBSD">child</a>, *<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, *<a href="/s?defs=old&amp;project=OpenBSD">old</a> = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;            \
<a class="l" name="526" href="#526">526</a>    <b>int</b> <a href="/s?defs=color&amp;project=OpenBSD">color</a>;                          \
<a class="l" name="527" href="#527">527</a>    <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)                \
<a class="l" name="528" href="#528">528</a>        <a href="/s?defs=child&amp;project=OpenBSD">child</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);               \
<a class="l" name="529" href="#529">529</a>    <b>else</b> <b>if</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)              \
<a class="hl" name="530" href="#530">530</a>        <a href="/s?defs=child&amp;project=OpenBSD">child</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);                \
<a class="l" name="531" href="#531">531</a>    <b>else</b> {                              \
<a class="l" name="532" href="#532">532</a>        <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=left&amp;project=OpenBSD">left</a>;                  \
<a class="l" name="533" href="#533">533</a>        <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);             \
<a class="l" name="534" href="#534">534</a>        <b>while</b> ((<a href="/s?defs=left&amp;project=OpenBSD">left</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))            \
<a class="l" name="535" href="#535">535</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a href="/s?defs=left&amp;project=OpenBSD">left</a>;                 \
<a class="l" name="536" href="#536">536</a>        <a href="/s?defs=child&amp;project=OpenBSD">child</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);               \
<a class="l" name="537" href="#537">537</a>        <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);             \
<a class="l" name="538" href="#538">538</a>        <a href="/s?defs=color&amp;project=OpenBSD">color</a> = <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);               \
<a class="l" name="539" href="#539">539</a>        <b>if</b> (<a href="/s?defs=child&amp;project=OpenBSD">child</a>)                      \
<a class="hl" name="540" href="#540">540</a>            <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=child&amp;project=OpenBSD">child</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;       \
<a class="l" name="541" href="#541">541</a>        <b>if</b> (<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>) {                       \
<a class="l" name="542" href="#542">542</a>            <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)      \
<a class="l" name="543" href="#543">543</a>                <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=child&amp;project=OpenBSD">child</a>;     \
<a class="l" name="544" href="#544">544</a>            <b>else</b>                        \
<a class="l" name="545" href="#545">545</a>                <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=child&amp;project=OpenBSD">child</a>;    \
<a class="l" name="546" href="#546">546</a>            <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>);             \
<a class="l" name="547" href="#547">547</a>        } <b>else</b>                          \
<a class="l" name="548" href="#548">548</a>            <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>) = <a href="/s?defs=child&amp;project=OpenBSD">child</a>;              \
<a class="l" name="549" href="#549">549</a>        <b>if</b> (<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=old&amp;project=OpenBSD">old</a>)           \
<a class="hl" name="550" href="#550">550</a>            <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;                   \
<a class="l" name="551" href="#551">551</a>        (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a> = (<a href="/s?defs=old&amp;project=OpenBSD">old</a>)-&gt;<a href="/s?defs=field&amp;project=OpenBSD">field</a>;                \
<a class="l" name="552" href="#552">552</a>        <b>if</b> (<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) {                \
<a class="l" name="553" href="#553">553</a>            <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=old&amp;project=OpenBSD">old</a>)\
<a class="l" name="554" href="#554">554</a>                <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;\
<a class="l" name="555" href="#555">555</a>            <b>else</b>                        \
<a class="l" name="556" href="#556">556</a>                <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;\
<a class="l" name="557" href="#557">557</a>            <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>));      \
<a class="l" name="558" href="#558">558</a>        } <b>else</b>                          \
<a class="l" name="559" href="#559">559</a>            <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;                \
<a class="hl" name="560" href="#560">560</a>        <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;        \
<a class="l" name="561" href="#561">561</a>        <b>if</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))               \
<a class="l" name="562" href="#562">562</a>            <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=old&amp;project=OpenBSD">old</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;   \
<a class="l" name="563" href="#563">563</a>        <b>if</b> (<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>) {                       \
<a class="l" name="564" href="#564">564</a>            <a href="/s?defs=left&amp;project=OpenBSD">left</a> = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;                  \
<a class="l" name="565" href="#565">565</a>            <b>do</b> {                        \
<a class="l" name="566" href="#566">566</a>                <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=left&amp;project=OpenBSD">left</a>);           \
<a class="l" name="567" href="#567">567</a>            } <b>while</b> ((<a href="/s?defs=left&amp;project=OpenBSD">left</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=left&amp;project=OpenBSD">left</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)));  \
<a class="l" name="568" href="#568">568</a>        }                           \
<a class="l" name="569" href="#569">569</a>        <b>goto</b> <a href="/s?defs=color&amp;project=OpenBSD">color</a>;                     \
<a class="hl" name="570" href="#570">570</a>    }                               \
<a class="l" name="571" href="#571">571</a>    <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);                 \
<a class="l" name="572" href="#572">572</a>    <a href="/s?defs=color&amp;project=OpenBSD">color</a> = <a class="d" href="#RB_COLOR">RB_COLOR</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);                   \
<a class="l" name="573" href="#573">573</a>    <b>if</b> (<a href="/s?defs=child&amp;project=OpenBSD">child</a>)                          \
<a class="l" name="574" href="#574">574</a>        <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=child&amp;project=OpenBSD">child</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>;           \
<a class="l" name="575" href="#575">575</a>    <b>if</b> (<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>) {                           \
<a class="l" name="576" href="#576">576</a>        <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) == <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)          \
<a class="l" name="577" href="#577">577</a>            <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=child&amp;project=OpenBSD">child</a>;         \
<a class="l" name="578" href="#578">578</a>        <b>else</b>                            \
<a class="l" name="579" href="#579">579</a>            <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=child&amp;project=OpenBSD">child</a>;        \
<a class="hl" name="580" href="#580">580</a>        <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>);                 \
<a class="l" name="581" href="#581">581</a>    } <b>else</b>                              \
<a class="l" name="582" href="#582">582</a>        <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>) = <a href="/s?defs=child&amp;project=OpenBSD">child</a>;                  \
<a class="l" name="583" href="#583">583</a><a href="/s?defs=color&amp;project=OpenBSD">color</a>:                                  \
<a class="l" name="584" href="#584">584</a>    <b>if</b> (<a href="/s?defs=color&amp;project=OpenBSD">color</a> == <a class="d" href="#RB_BLACK">RB_BLACK</a>)                      \
<a class="l" name="585" href="#585">585</a>        <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_REMOVE_COLOR&amp;project=OpenBSD">_RB_REMOVE_COLOR</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=child&amp;project=OpenBSD">child</a>);        \
<a class="l" name="586" href="#586">586</a>    <b>return</b> (<a href="/s?defs=old&amp;project=OpenBSD">old</a>);                           \
<a class="l" name="587" href="#587">587</a>}                                   \
<a class="l" name="588" href="#588">588</a>                                    \
<a class="l" name="589" href="#589">589</a><span class="c">/* Inserts a node into the RB tree */</span>                   \
<a class="hl" name="590" href="#590">590</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="l" name="591" href="#591">591</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_INSERT&amp;project=OpenBSD">_RB_INSERT</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)           \
<a class="l" name="592" href="#592">592</a>{                                   \
<a class="l" name="593" href="#593">593</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                       \
<a class="l" name="594" href="#594">594</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                 \
<a class="l" name="595" href="#595">595</a>    <b>int</b> <a href="/s?defs=comp&amp;project=OpenBSD">comp</a> = 0;                           \
<a class="l" name="596" href="#596">596</a>    <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>);                        \
<a class="l" name="597" href="#597">597</a>    <b>while</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>) {                           \
<a class="l" name="598" href="#598">598</a>        <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                       \
<a class="l" name="599" href="#599">599</a>        <a href="/s?defs=comp&amp;project=OpenBSD">comp</a> = (<a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>)(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>);              \
<a class="hl" name="600" href="#600">600</a>        <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &lt; 0)                       \
<a class="l" name="601" href="#601">601</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="l" name="602" href="#602">602</a>        <b>else</b> <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &gt; 0)                  \
<a class="l" name="603" href="#603">603</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="604" href="#604">604</a>        <b>else</b>                            \
<a class="l" name="605" href="#605">605</a>            <b>return</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                   \
<a class="l" name="606" href="#606">606</a>    }                               \
<a class="l" name="607" href="#607">607</a>    <a class="d" href="#RB_SET">RB_SET</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);                 \
<a class="l" name="608" href="#608">608</a>    <b>if</b> (<a href="/s?defs=parent&amp;project=OpenBSD">parent</a> != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>) {                       \
<a class="l" name="609" href="#609">609</a>        <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &lt; 0)                       \
<a class="hl" name="610" href="#610">610</a>            <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;           \
<a class="l" name="611" href="#611">611</a>        <b>else</b>                            \
<a class="l" name="612" href="#612">612</a>            <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;          \
<a class="l" name="613" href="#613">613</a>        <a class="d" href="#RB_AUGMENT">RB_AUGMENT</a>(<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>);                 \
<a class="l" name="614" href="#614">614</a>    } <b>else</b>                              \
<a class="l" name="615" href="#615">615</a>        <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>) = <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>;                    \
<a class="l" name="616" href="#616">616</a>    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_INSERT_COLOR&amp;project=OpenBSD">_RB_INSERT_COLOR</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);              \
<a class="l" name="617" href="#617">617</a>    <b>return</b> (<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                          \
<a class="l" name="618" href="#618">618</a>}                                   \
<a class="l" name="619" href="#619">619</a>                                    \
<a class="hl" name="620" href="#620">620</a><span class="c">/* Finds the node with the same key as elm */</span>               \
<a class="l" name="621" href="#621">621</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="l" name="622" href="#622">622</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_FIND&amp;project=OpenBSD">_RB_FIND</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)         \
<a class="l" name="623" href="#623">623</a>{                                   \
<a class="l" name="624" href="#624">624</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>);               \
<a class="l" name="625" href="#625">625</a>    <b>int</b> <a href="/s?defs=comp&amp;project=OpenBSD">comp</a>;                           \
<a class="l" name="626" href="#626">626</a>    <b>while</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>) {                           \
<a class="l" name="627" href="#627">627</a>        <a href="/s?defs=comp&amp;project=OpenBSD">comp</a> = <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                   \
<a class="l" name="628" href="#628">628</a>        <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &lt; 0)                       \
<a class="l" name="629" href="#629">629</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="hl" name="630" href="#630">630</a>        <b>else</b> <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &gt; 0)                  \
<a class="l" name="631" href="#631">631</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="632" href="#632">632</a>        <b>else</b>                            \
<a class="l" name="633" href="#633">633</a>            <b>return</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                   \
<a class="l" name="634" href="#634">634</a>    }                               \
<a class="l" name="635" href="#635">635</a>    <b>return</b> (<a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);                          \
<a class="l" name="636" href="#636">636</a>}                                   \
<a class="l" name="637" href="#637">637</a>                                    \
<a class="l" name="638" href="#638">638</a><span class="c">/* Finds the first node greater than or equal to the search key */</span>  \
<a class="l" name="639" href="#639">639</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="hl" name="640" href="#640">640</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NFIND&amp;project=OpenBSD">_RB_NFIND</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)            \
<a class="l" name="641" href="#641">641</a>{                                   \
<a class="l" name="642" href="#642">642</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>);               \
<a class="l" name="643" href="#643">643</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=res&amp;project=OpenBSD">res</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                    \
<a class="l" name="644" href="#644">644</a>    <b>int</b> <a href="/s?defs=comp&amp;project=OpenBSD">comp</a>;                           \
<a class="l" name="645" href="#645">645</a>    <b>while</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>) {                           \
<a class="l" name="646" href="#646">646</a>        <a href="/s?defs=comp&amp;project=OpenBSD">comp</a> = <a href="/s?defs=cmp&amp;project=OpenBSD">cmp</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                   \
<a class="l" name="647" href="#647">647</a>        <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &lt; 0) {                     \
<a class="l" name="648" href="#648">648</a>            <a href="/s?defs=res&amp;project=OpenBSD">res</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                  \
<a class="l" name="649" href="#649">649</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="hl" name="650" href="#650">650</a>        }                           \
<a class="l" name="651" href="#651">651</a>        <b>else</b> <b>if</b> (<a href="/s?defs=comp&amp;project=OpenBSD">comp</a> &gt; 0)                  \
<a class="l" name="652" href="#652">652</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="653" href="#653">653</a>        <b>else</b>                            \
<a class="l" name="654" href="#654">654</a>            <b>return</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>);                   \
<a class="l" name="655" href="#655">655</a>    }                               \
<a class="l" name="656" href="#656">656</a>    <b>return</b> (<a href="/s?defs=res&amp;project=OpenBSD">res</a>);                           \
<a class="l" name="657" href="#657">657</a>}                                   \
<a class="l" name="658" href="#658">658</a>                                    \
<a class="l" name="659" href="#659">659</a><span class="c">/* ARGSUSED */</span>                              \
<a class="hl" name="660" href="#660">660</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="l" name="661" href="#661">661</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NEXT&amp;project=OpenBSD">_RB_NEXT</a>(<b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                    \
<a class="l" name="662" href="#662">662</a>{                                   \
<a class="l" name="663" href="#663">663</a>    <b>if</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) {                 \
<a class="l" name="664" href="#664">664</a>        <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);             \
<a class="l" name="665" href="#665">665</a>        <b>while</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))             \
<a class="l" name="666" href="#666">666</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="l" name="667" href="#667">667</a>    } <b>else</b> {                            \
<a class="l" name="668" href="#668">668</a>        <b>if</b> (<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) &amp;&amp;                \
<a class="l" name="669" href="#669">669</a>            (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a> == <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>))) \
<a class="hl" name="670" href="#670">670</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);            \
<a class="l" name="671" href="#671">671</a>        <b>else</b> {                          \
<a class="l" name="672" href="#672">672</a>            <b>while</b> (<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) &amp;&amp;         \
<a class="l" name="673" href="#673">673</a>                (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a> == <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))\
<a class="l" name="674" href="#674">674</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);        \
<a class="l" name="675" href="#675">675</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);            \
<a class="l" name="676" href="#676">676</a>        }                           \
<a class="l" name="677" href="#677">677</a>    }                               \
<a class="l" name="678" href="#678">678</a>    <b>return</b> (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                           \
<a class="l" name="679" href="#679">679</a>}                                   \
<a class="hl" name="680" href="#680">680</a>                                    \
<a class="l" name="681" href="#681">681</a><span class="c">/* ARGSUSED */</span>                              \
<a class="l" name="682" href="#682">682</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="l" name="683" href="#683">683</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_PREV&amp;project=OpenBSD">_RB_PREV</a>(<b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                    \
<a class="l" name="684" href="#684">684</a>{                                   \
<a class="l" name="685" href="#685">685</a>    <b>if</b> (<a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>)) {                  \
<a class="l" name="686" href="#686">686</a>        <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);              \
<a class="l" name="687" href="#687">687</a>        <b>while</b> (<a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>))                \
<a class="l" name="688" href="#688">688</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="689" href="#689">689</a>    } <b>else</b> {                            \
<a class="hl" name="690" href="#690">690</a>        <b>if</b> (<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) &amp;&amp;                \
<a class="l" name="691" href="#691">691</a>            (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a> == <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))    \
<a class="l" name="692" href="#692">692</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);            \
<a class="l" name="693" href="#693">693</a>        <b>else</b> {                          \
<a class="l" name="694" href="#694">694</a>            <b>while</b> (<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>) &amp;&amp;         \
<a class="l" name="695" href="#695">695</a>                (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a> == <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>), <a href="/s?defs=field&amp;project=OpenBSD">field</a>)))\
<a class="l" name="696" href="#696">696</a>                <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);        \
<a class="l" name="697" href="#697">697</a>            <a href="/s?defs=elm&amp;project=OpenBSD">elm</a> = <a class="d" href="#RB_PARENT">RB_PARENT</a>(<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);            \
<a class="l" name="698" href="#698">698</a>        }                           \
<a class="l" name="699" href="#699">699</a>    }                               \
<a class="hl" name="700" href="#700">700</a>    <b>return</b> (<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);                           \
<a class="l" name="701" href="#701">701</a>}                                   \
<a class="l" name="702" href="#702">702</a>                                    \
<a class="l" name="703" href="#703">703</a><a href="/s?defs=attr&amp;project=OpenBSD">attr</a> <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *                          \
<a class="l" name="704" href="#704">704</a><a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_MINMAX&amp;project=OpenBSD">_RB_MINMAX</a>(<b>struct</b> <a href="/s?defs=name&amp;project=OpenBSD">name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>int</b> <a href="/s?defs=val&amp;project=OpenBSD">val</a>)                \
<a class="l" name="705" href="#705">705</a>{                                   \
<a class="l" name="706" href="#706">706</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_ROOT">RB_ROOT</a>(<a href="/s?defs=head&amp;project=OpenBSD">head</a>);               \
<a class="l" name="707" href="#707">707</a>    <b>struct</b> <a href="/s?defs=type&amp;project=OpenBSD">type</a> *<a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                 \
<a class="l" name="708" href="#708">708</a>    <b>while</b> (<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>) {                           \
<a class="l" name="709" href="#709">709</a>        <a href="/s?defs=parent&amp;project=OpenBSD">parent</a> = <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>;                       \
<a class="hl" name="710" href="#710">710</a>        <b>if</b> (<a href="/s?defs=val&amp;project=OpenBSD">val</a> &lt; 0)                        \
<a class="l" name="711" href="#711">711</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_LEFT">RB_LEFT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);          \
<a class="l" name="712" href="#712">712</a>        <b>else</b>                            \
<a class="l" name="713" href="#713">713</a>            <a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a> = <a class="d" href="#RB_RIGHT">RB_RIGHT</a>(<a href="/s?defs=tmp&amp;project=OpenBSD">tmp</a>, <a href="/s?defs=field&amp;project=OpenBSD">field</a>);         \
<a class="l" name="714" href="#714">714</a>    }                               \
<a class="l" name="715" href="#715">715</a>    <b>return</b> (<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>);                        \
<a class="l" name="716" href="#716">716</a>}
<a class="l" name="717" href="#717">717</a>
<a class="l" name="718" href="#718">718</a>#<b>define</b> <a class="xm" name="RB_NEGINF"/><a href="/s?refs=RB_NEGINF&amp;project=OpenBSD" class="xm">RB_NEGINF</a>   -<span class="n">1</span>
<a class="l" name="719" href="#719">719</a>#<b>define</b> <a class="xm" name="RB_INF"/><a href="/s?refs=RB_INF&amp;project=OpenBSD" class="xm">RB_INF</a>  <span class="n">1</span>
<a class="hl" name="720" href="#720">720</a>
<a class="l" name="721" href="#721">721</a>#<b>define</b> <a class="xm" name="RB_INSERT"/><a href="/s?refs=RB_INSERT&amp;project=OpenBSD" class="xm">RB_INSERT</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)   <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_INSERT&amp;project=OpenBSD">_RB_INSERT</a>(x, y)
<a class="l" name="722" href="#722">722</a>#<b>define</b> <a class="xm" name="RB_REMOVE"/><a href="/s?refs=RB_REMOVE&amp;project=OpenBSD" class="xm">RB_REMOVE</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)   <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_REMOVE&amp;project=OpenBSD">_RB_REMOVE</a>(x, y)
<a class="l" name="723" href="#723">723</a>#<b>define</b> <a class="xm" name="RB_FIND"/><a href="/s?refs=RB_FIND&amp;project=OpenBSD" class="xm">RB_FIND</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y) <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_FIND&amp;project=OpenBSD">_RB_FIND</a>(x, y)
<a class="l" name="724" href="#724">724</a>#<b>define</b> <a class="xm" name="RB_NFIND"/><a href="/s?refs=RB_NFIND&amp;project=OpenBSD" class="xm">RB_NFIND</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y)    <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NFIND&amp;project=OpenBSD">_RB_NFIND</a>(x, y)
<a class="l" name="725" href="#725">725</a>#<b>define</b> <a class="xm" name="RB_NEXT"/><a href="/s?refs=RB_NEXT&amp;project=OpenBSD" class="xm">RB_NEXT</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y) <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NEXT&amp;project=OpenBSD">_RB_NEXT</a>(y)
<a class="l" name="726" href="#726">726</a>#<b>define</b> <a class="xm" name="RB_PREV"/><a href="/s?refs=RB_PREV&amp;project=OpenBSD" class="xm">RB_PREV</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x, y) <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_PREV&amp;project=OpenBSD">_RB_PREV</a>(y)
<a class="l" name="727" href="#727">727</a>#<b>define</b> <a class="xm" name="RB_MIN"/><a href="/s?refs=RB_MIN&amp;project=OpenBSD" class="xm">RB_MIN</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x)     <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_MINMAX&amp;project=OpenBSD">_RB_MINMAX</a>(x, <a class="d" href="#RB_NEGINF">RB_NEGINF</a>)
<a class="l" name="728" href="#728">728</a>#<b>define</b> <a class="xm" name="RB_MAX"/><a href="/s?refs=RB_MAX&amp;project=OpenBSD" class="xm">RB_MAX</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, x)     <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_MINMAX&amp;project=OpenBSD">_RB_MINMAX</a>(x, <a class="d" href="#RB_INF">RB_INF</a>)
<a class="l" name="729" href="#729">729</a>
<a class="hl" name="730" href="#730">730</a>#<b>define</b> <a class="xm" name="RB_FOREACH"/><a href="/s?refs=RB_FOREACH&amp;project=OpenBSD" class="xm">RB_FOREACH</a>(x, <a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>)                   \
<a class="l" name="731" href="#731">731</a>    <b>for</b> ((x) = <a class="d" href="#RB_MIN">RB_MIN</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>);                  \
<a class="l" name="732" href="#732">732</a>         (x) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                       \
<a class="l" name="733" href="#733">733</a>         (x) = <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NEXT&amp;project=OpenBSD">_RB_NEXT</a>(x))
<a class="l" name="734" href="#734">734</a>
<a class="l" name="735" href="#735">735</a>#<b>define</b> <a class="xm" name="RB_FOREACH_SAFE"/><a href="/s?refs=RB_FOREACH_SAFE&amp;project=OpenBSD" class="xm">RB_FOREACH_SAFE</a>(x, <a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>, y)               \
<a class="l" name="736" href="#736">736</a>    <b>for</b> ((x) = <a class="d" href="#RB_MIN">RB_MIN</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>);                  \
<a class="l" name="737" href="#737">737</a>        ((x) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>) &amp;&amp; ((y) = <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_NEXT&amp;project=OpenBSD">_RB_NEXT</a>(x), <span class="n">1</span>);      \
<a class="l" name="738" href="#738">738</a>         (x) = (y))
<a class="l" name="739" href="#739">739</a>
<a class="hl" name="740" href="#740">740</a>#<b>define</b> <a class="xm" name="RB_FOREACH_REVERSE"/><a href="/s?refs=RB_FOREACH_REVERSE&amp;project=OpenBSD" class="xm">RB_FOREACH_REVERSE</a>(x, <a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>)               \
<a class="l" name="741" href="#741">741</a>    <b>for</b> ((x) = <a class="d" href="#RB_MAX">RB_MAX</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>);                  \
<a class="l" name="742" href="#742">742</a>         (x) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                       \
<a class="l" name="743" href="#743">743</a>         (x) = <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_PREV&amp;project=OpenBSD">_RB_PREV</a>(x))
<a class="l" name="744" href="#744">744</a>
<a class="l" name="745" href="#745">745</a>#<b>define</b> <a class="xm" name="RB_FOREACH_REVERSE_SAFE"/><a href="/s?refs=RB_FOREACH_REVERSE_SAFE&amp;project=OpenBSD" class="xm">RB_FOREACH_REVERSE_SAFE</a>(x, <a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>, y)           \
<a class="l" name="746" href="#746">746</a>    <b>for</b> ((x) = <a class="d" href="#RB_MAX">RB_MAX</a>(<a href="/s?defs=name&amp;project=OpenBSD">name</a>, <a href="/s?defs=head&amp;project=OpenBSD">head</a>);                  \
<a class="l" name="747" href="#747">747</a>        ((x) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>) &amp;&amp; ((y) = <a href="/s?defs=name&amp;project=OpenBSD">name</a>##<a href="/s?defs=_RB_PREV&amp;project=OpenBSD">_RB_PREV</a>(x), <span class="n">1</span>);      \
<a class="l" name="748" href="#748">748</a>         (x) = (y))
<a class="l" name="749" href="#749">749</a>
<a class="hl" name="750" href="#750">750</a>
<a class="l" name="751" href="#751">751</a><span class="c">/*
<a class="l" name="752" href="#752">752</a> * Copyright (c) 2016 David Gwynne &lt;dlg@openbsd.org&gt;
<a class="l" name="753" href="#753">753</a> *
<a class="l" name="754" href="#754">754</a> * Permission to use, copy, modify, and distribute this software for any
<a class="l" name="755" href="#755">755</a> * purpose with or without fee is hereby granted, provided that the above
<a class="l" name="756" href="#756">756</a> * copyright notice and this permission notice appear in all copies.
<a class="l" name="757" href="#757">757</a> *
<a class="l" name="758" href="#758">758</a> * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
<a class="l" name="759" href="#759">759</a> * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
<a class="hl" name="760" href="#760">760</a> * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
<a class="l" name="761" href="#761">761</a> * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
<a class="l" name="762" href="#762">762</a> * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
<a class="l" name="763" href="#763">763</a> * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
<a class="l" name="764" href="#764">764</a> * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
<a class="l" name="765" href="#765">765</a> */</span>
<a class="l" name="766" href="#766">766</a>
<a class="l" name="767" href="#767">767</a><b>struct</b> <a class="xs" name="rb_type"/><a href="/s?refs=rb_type&amp;project=OpenBSD" class="xs">rb_type</a> {
<a class="l" name="768" href="#768">768</a>    <b>int</b>     (*<a class="xmb" name="t_compare"/><a href="/s?refs=t_compare&amp;project=OpenBSD" class="xmb">t_compare</a>)(<b>const</b> <b>void</b> *, <b>const</b> <b>void</b> *);
<a class="l" name="769" href="#769">769</a>    <b>void</b>        (*<a class="xmb" name="t_augment"/><a href="/s?refs=t_augment&amp;project=OpenBSD" class="xmb">t_augment</a>)(<b>void</b> *);
<a class="hl" name="770" href="#770">770</a>    <b>unsigned</b> <b>int</b>      <a class="xmb" name="t_offset"/><a href="/s?refs=t_offset&amp;project=OpenBSD" class="xmb">t_offset</a>; <span class="c">/* offset of rb_entry in type */</span>
<a class="l" name="771" href="#771">771</a>};
<a class="l" name="772" href="#772">772</a>
<a class="l" name="773" href="#773">773</a><b>struct</b> <a class="xs" name="rb_tree"/><a href="/s?refs=rb_tree&amp;project=OpenBSD" class="xs">rb_tree</a> {
<a class="l" name="774" href="#774">774</a>    <b>struct</b> <a class="d" href="#rb_entry">rb_entry</a> *<a class="xmb" name="rbt_root"/><a href="/s?refs=rbt_root&amp;project=OpenBSD" class="xmb">rbt_root</a>;
<a class="l" name="775" href="#775">775</a>};
<a class="l" name="776" href="#776">776</a>
<a class="l" name="777" href="#777">777</a><b>struct</b> <a class="xs" name="rb_entry"/><a href="/s?refs=rb_entry&amp;project=OpenBSD" class="xs">rb_entry</a> {
<a class="l" name="778" href="#778">778</a>    <b>struct</b> <a class="d" href="#rb_entry">rb_entry</a>  *<a class="xmb" name="rbt_parent"/><a href="/s?refs=rbt_parent&amp;project=OpenBSD" class="xmb">rbt_parent</a>;
<a class="l" name="779" href="#779">779</a>    <b>struct</b> <a class="d" href="#rb_entry">rb_entry</a>  *<a class="xmb" name="rbt_left"/><a href="/s?refs=rbt_left&amp;project=OpenBSD" class="xmb">rbt_left</a>;
<a class="hl" name="780" href="#780">780</a>    <b>struct</b> <a class="d" href="#rb_entry">rb_entry</a>  *<a class="xmb" name="rbt_right"/><a href="/s?refs=rbt_right&amp;project=OpenBSD" class="xmb">rbt_right</a>;
<a class="l" name="781" href="#781">781</a>    <b>unsigned</b> <b>int</b>      <a class="xmb" name="rbt_color"/><a href="/s?refs=rbt_color&amp;project=OpenBSD" class="xmb">rbt_color</a>;
<a class="l" name="782" href="#782">782</a>};
<a class="l" name="783" href="#783">783</a>
<a class="l" name="784" href="#784">784</a>#<b>define</b> <a class="xm" name="RBT_HEAD"/><a href="/s?refs=RBT_HEAD&amp;project=OpenBSD" class="xm">RBT_HEAD</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>)                      \
<a class="l" name="785" href="#785">785</a><b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> {                              \
<a class="l" name="786" href="#786">786</a>    <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> <a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>;                    \
<a class="l" name="787" href="#787">787</a>}
<a class="l" name="788" href="#788">788</a>
<a class="l" name="789" href="#789">789</a>#<b>define</b> <a class="xm" name="RBT_ENTRY"/><a href="/s?refs=RBT_ENTRY&amp;project=OpenBSD" class="xm">RBT_ENTRY</a>(<a href="/s?defs=_type&amp;project=OpenBSD">_type</a>)    <b>struct</b> <a class="d" href="#rb_entry">rb_entry</a>
<a class="hl" name="790" href="#790">790</a>
<a class="l" name="791" href="#791">791</a><b>static</b> <b>inline</b> <b>void</b>
<a class="l" name="792" href="#792">792</a><a class="xf" name="_rb_init"/><a href="/s?refs=_rb_init&amp;project=OpenBSD" class="xf">_rb_init</a>(<b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *<a class="xa" name="rbt"/><a href="/s?refs=rbt&amp;project=OpenBSD" class="xa">rbt</a>)
<a class="l" name="793" href="#793">793</a>{
<a class="l" name="794" href="#794">794</a>    <a href="/s?defs=rbt&amp;project=OpenBSD">rbt</a>-&gt;<a class="d" href="#rbt_root">rbt_root</a> = <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;
<a class="l" name="795" href="#795">795</a>}
<a class="l" name="796" href="#796">796</a>
<a class="l" name="797" href="#797">797</a><b>static</b> <b>inline</b> <b>int</b>
<a class="l" name="798" href="#798">798</a><a class="xf" name="_rb_empty"/><a href="/s?refs=_rb_empty&amp;project=OpenBSD" class="xf">_rb_empty</a>(<b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *<a class="xa" name="rbt"/><a href="/s?refs=rbt&amp;project=OpenBSD" class="xa">rbt</a>)
<a class="l" name="799" href="#799">799</a>{
<a class="hl" name="800" href="#800">800</a>    <b>return</b> (<a href="/s?defs=rbt&amp;project=OpenBSD">rbt</a>-&gt;<a class="d" href="#rbt_root">rbt_root</a> == <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>);
<a class="l" name="801" href="#801">801</a>}
<a class="l" name="802" href="#802">802</a>
<a class="l" name="803" href="#803">803</a><b>void</b>    *<a href="/s?defs=_rb_insert&amp;project=OpenBSD">_rb_insert</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *, <b>void</b> *);
<a class="l" name="804" href="#804">804</a><b>void</b>    *<a href="/s?defs=_rb_remove&amp;project=OpenBSD">_rb_remove</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *, <b>void</b> *);
<a class="l" name="805" href="#805">805</a><b>void</b>    *<a href="/s?defs=_rb_find&amp;project=OpenBSD">_rb_find</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *, <b>const</b> <b>void</b> *);
<a class="l" name="806" href="#806">806</a><b>void</b>    *<a href="/s?defs=_rb_nfind&amp;project=OpenBSD">_rb_nfind</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *, <b>const</b> <b>void</b> *);
<a class="l" name="807" href="#807">807</a><b>void</b>    *<a href="/s?defs=_rb_root&amp;project=OpenBSD">_rb_root</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *);
<a class="l" name="808" href="#808">808</a><b>void</b>    *<a href="/s?defs=_rb_min&amp;project=OpenBSD">_rb_min</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *);
<a class="l" name="809" href="#809">809</a><b>void</b>    *<a href="/s?defs=_rb_max&amp;project=OpenBSD">_rb_max</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>struct</b> <a class="d" href="#rb_tree">rb_tree</a> *);
<a class="hl" name="810" href="#810">810</a><b>void</b>    *<a href="/s?defs=_rb_next&amp;project=OpenBSD">_rb_next</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *);
<a class="l" name="811" href="#811">811</a><b>void</b>    *<a href="/s?defs=_rb_prev&amp;project=OpenBSD">_rb_prev</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *);
<a class="l" name="812" href="#812">812</a><b>void</b>    *<a href="/s?defs=_rb_left&amp;project=OpenBSD">_rb_left</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *);
<a class="l" name="813" href="#813">813</a><b>void</b>    *<a href="/s?defs=_rb_right&amp;project=OpenBSD">_rb_right</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *);
<a class="l" name="814" href="#814">814</a><b>void</b>    *<a href="/s?defs=_rb_parent&amp;project=OpenBSD">_rb_parent</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *);
<a class="l" name="815" href="#815">815</a><b>void</b>     <a href="/s?defs=_rb_set_left&amp;project=OpenBSD">_rb_set_left</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *, <b>void</b> *);
<a class="l" name="816" href="#816">816</a><b>void</b>     <a href="/s?defs=_rb_set_right&amp;project=OpenBSD">_rb_set_right</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *, <b>void</b> *);
<a class="l" name="817" href="#817">817</a><b>void</b>     <a href="/s?defs=_rb_set_parent&amp;project=OpenBSD">_rb_set_parent</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *, <b>void</b> *);
<a class="l" name="818" href="#818">818</a><b>void</b>     <a href="/s?defs=_rb_poison&amp;project=OpenBSD">_rb_poison</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *, <b>unsigned</b> <b>long</b>);
<a class="l" name="819" href="#819">819</a><b>int</b>  <a href="/s?defs=_rb_check&amp;project=OpenBSD">_rb_check</a>(<b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *, <b>void</b> *, <b>unsigned</b> <b>long</b>);
<a class="hl" name="820" href="#820">820</a>
<a class="l" name="821" href="#821">821</a>#<b>define</b> <a class="xm" name="RBT_INITIALIZER"/><a href="/s?refs=RBT_INITIALIZER&amp;project=OpenBSD" class="xm">RBT_INITIALIZER</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)  { { <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> } }
<a class="l" name="822" href="#822">822</a>
<a class="l" name="823" href="#823">823</a>#<b>define</b> <a class="xm" name="RBT_PROTOTYPE"/><a href="/s?refs=RBT_PROTOTYPE&amp;project=OpenBSD" class="xm">RBT_PROTOTYPE</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>, <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>)           \
<a class="l" name="824" href="#824">824</a><b>extern</b> <b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *<b>const</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>;            \
<a class="l" name="825" href="#825">825</a>                                    \
<a class="l" name="826" href="#826">826</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>void</b>                     \
<a class="l" name="827" href="#827">827</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_INIT&amp;project=OpenBSD">_RBT_INIT</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>)                    \
<a class="l" name="828" href="#828">828</a>{                                   \
<a class="l" name="829" href="#829">829</a>    <a class="d" href="#_rb_init">_rb_init</a>(&amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>);                  \
<a class="hl" name="830" href="#830">830</a>}                                   \
<a class="l" name="831" href="#831">831</a>                                    \
<a class="l" name="832" href="#832">832</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="833" href="#833">833</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_INSERT&amp;project=OpenBSD">_RBT_INSERT</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)       \
<a class="l" name="834" href="#834">834</a>{                                   \
<a class="l" name="835" href="#835">835</a>    <b>return</b> <a href="/s?defs=_rb_insert&amp;project=OpenBSD">_rb_insert</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);  \
<a class="l" name="836" href="#836">836</a>}                                   \
<a class="l" name="837" href="#837">837</a>                                    \
<a class="l" name="838" href="#838">838</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="839" href="#839">839</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_REMOVE&amp;project=OpenBSD">_RBT_REMOVE</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)       \
<a class="hl" name="840" href="#840">840</a>{                                   \
<a class="l" name="841" href="#841">841</a>    <b>return</b> <a href="/s?defs=_rb_remove&amp;project=OpenBSD">_rb_remove</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);  \
<a class="l" name="842" href="#842">842</a>}                                   \
<a class="l" name="843" href="#843">843</a>                                    \
<a class="l" name="844" href="#844">844</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="845" href="#845">845</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_FIND&amp;project=OpenBSD">_RBT_FIND</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>const</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=key&amp;project=OpenBSD">key</a>)       \
<a class="l" name="846" href="#846">846</a>{                                   \
<a class="l" name="847" href="#847">847</a>    <b>return</b> <a href="/s?defs=_rb_find&amp;project=OpenBSD">_rb_find</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>, <a href="/s?defs=key&amp;project=OpenBSD">key</a>);    \
<a class="l" name="848" href="#848">848</a>}                                   \
<a class="l" name="849" href="#849">849</a>                                    \
<a class="hl" name="850" href="#850">850</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="851" href="#851">851</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_NFIND&amp;project=OpenBSD">_RBT_NFIND</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>, <b>const</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=key&amp;project=OpenBSD">key</a>)      \
<a class="l" name="852" href="#852">852</a>{                                   \
<a class="l" name="853" href="#853">853</a>    <b>return</b> <a href="/s?defs=_rb_nfind&amp;project=OpenBSD">_rb_nfind</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>, <a href="/s?defs=key&amp;project=OpenBSD">key</a>);   \
<a class="l" name="854" href="#854">854</a>}                                   \
<a class="l" name="855" href="#855">855</a>                                    \
<a class="l" name="856" href="#856">856</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="857" href="#857">857</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_ROOT&amp;project=OpenBSD">_RBT_ROOT</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>)                    \
<a class="l" name="858" href="#858">858</a>{                                   \
<a class="l" name="859" href="#859">859</a>    <b>return</b> <a href="/s?defs=_rb_root&amp;project=OpenBSD">_rb_root</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>);     \
<a class="hl" name="860" href="#860">860</a>}                                   \
<a class="l" name="861" href="#861">861</a>                                    \
<a class="l" name="862" href="#862">862</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>int</b>                      \
<a class="l" name="863" href="#863">863</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_EMPTY&amp;project=OpenBSD">_RBT_EMPTY</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>)                   \
<a class="l" name="864" href="#864">864</a>{                                   \
<a class="l" name="865" href="#865">865</a>    <b>return</b> <a class="d" href="#_rb_empty">_rb_empty</a>(&amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>);              \
<a class="l" name="866" href="#866">866</a>}                                   \
<a class="l" name="867" href="#867">867</a>                                    \
<a class="l" name="868" href="#868">868</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="869" href="#869">869</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_MIN&amp;project=OpenBSD">_RBT_MIN</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>)                 \
<a class="hl" name="870" href="#870">870</a>{                                   \
<a class="l" name="871" href="#871">871</a>    <b>return</b> <a href="/s?defs=_rb_min&amp;project=OpenBSD">_rb_min</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>);      \
<a class="l" name="872" href="#872">872</a>}                                   \
<a class="l" name="873" href="#873">873</a>                                    \
<a class="l" name="874" href="#874">874</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="875" href="#875">875</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_MAX&amp;project=OpenBSD">_RBT_MAX</a>(<b>struct</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a> *<a href="/s?defs=head&amp;project=OpenBSD">head</a>)                 \
<a class="l" name="876" href="#876">876</a>{                                   \
<a class="l" name="877" href="#877">877</a>    <b>return</b> <a href="/s?defs=_rb_max&amp;project=OpenBSD">_rb_max</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, &amp;<a href="/s?defs=head&amp;project=OpenBSD">head</a>-&gt;<a href="/s?defs=rbh_root&amp;project=OpenBSD">rbh_root</a>);      \
<a class="l" name="878" href="#878">878</a>}                                   \
<a class="l" name="879" href="#879">879</a>                                    \
<a class="hl" name="880" href="#880">880</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="881" href="#881">881</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_NEXT&amp;project=OpenBSD">_RBT_NEXT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                 \
<a class="l" name="882" href="#882">882</a>{                                   \
<a class="l" name="883" href="#883">883</a>    <b>return</b> <a href="/s?defs=_rb_next&amp;project=OpenBSD">_rb_next</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);             \
<a class="l" name="884" href="#884">884</a>}                                   \
<a class="l" name="885" href="#885">885</a>                                    \
<a class="l" name="886" href="#886">886</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="887" href="#887">887</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_PREV&amp;project=OpenBSD">_RBT_PREV</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                 \
<a class="l" name="888" href="#888">888</a>{                                   \
<a class="l" name="889" href="#889">889</a>    <b>return</b> <a href="/s?defs=_rb_prev&amp;project=OpenBSD">_rb_prev</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);             \
<a class="hl" name="890" href="#890">890</a>}                                   \
<a class="l" name="891" href="#891">891</a>                                    \
<a class="l" name="892" href="#892">892</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="893" href="#893">893</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_LEFT&amp;project=OpenBSD">_RBT_LEFT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                 \
<a class="l" name="894" href="#894">894</a>{                                   \
<a class="l" name="895" href="#895">895</a>    <b>return</b> <a href="/s?defs=_rb_left&amp;project=OpenBSD">_rb_left</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);             \
<a class="l" name="896" href="#896">896</a>}                                   \
<a class="l" name="897" href="#897">897</a>                                    \
<a class="l" name="898" href="#898">898</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="899" href="#899">899</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_RIGHT&amp;project=OpenBSD">_RBT_RIGHT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                    \
<a class="hl" name="900" href="#900">900</a>{                                   \
<a class="l" name="901" href="#901">901</a>    <b>return</b> <a href="/s?defs=_rb_right&amp;project=OpenBSD">_rb_right</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);            \
<a class="l" name="902" href="#902">902</a>}                                   \
<a class="l" name="903" href="#903">903</a>                                    \
<a class="l" name="904" href="#904">904</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *                   \
<a class="l" name="905" href="#905">905</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_PARENT&amp;project=OpenBSD">_RBT_PARENT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>)                   \
<a class="l" name="906" href="#906">906</a>{                                   \
<a class="l" name="907" href="#907">907</a>    <b>return</b> <a href="/s?defs=_rb_parent&amp;project=OpenBSD">_rb_parent</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>);           \
<a class="l" name="908" href="#908">908</a>}                                   \
<a class="l" name="909" href="#909">909</a>                                    \
<a class="hl" name="910" href="#910">910</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>void</b>                     \
<a class="l" name="911" href="#911">911</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_SET_LEFT&amp;project=OpenBSD">_RBT_SET_LEFT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=left&amp;project=OpenBSD">left</a>)     \
<a class="l" name="912" href="#912">912</a>{                                   \
<a class="l" name="913" href="#913">913</a>    <b>return</b> <a href="/s?defs=_rb_set_left&amp;project=OpenBSD">_rb_set_left</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=left&amp;project=OpenBSD">left</a>);       \
<a class="l" name="914" href="#914">914</a>}                                   \
<a class="l" name="915" href="#915">915</a>                                    \
<a class="l" name="916" href="#916">916</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>void</b>                     \
<a class="l" name="917" href="#917">917</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_SET_RIGHT&amp;project=OpenBSD">_RBT_SET_RIGHT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=right&amp;project=OpenBSD">right</a>)       \
<a class="l" name="918" href="#918">918</a>{                                   \
<a class="l" name="919" href="#919">919</a>    <b>return</b> <a href="/s?defs=_rb_set_right&amp;project=OpenBSD">_rb_set_right</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=right&amp;project=OpenBSD">right</a>);     \
<a class="hl" name="920" href="#920">920</a>}                                   \
<a class="l" name="921" href="#921">921</a>                                    \
<a class="l" name="922" href="#922">922</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>void</b>                     \
<a class="l" name="923" href="#923">923</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_SET_PARENT&amp;project=OpenBSD">_RBT_SET_PARENT</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=parent&amp;project=OpenBSD">parent</a>)     \
<a class="l" name="924" href="#924">924</a>{                                   \
<a class="l" name="925" href="#925">925</a>    <b>return</b> <a href="/s?defs=_rb_set_parent&amp;project=OpenBSD">_rb_set_parent</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=parent&amp;project=OpenBSD">parent</a>);       \
<a class="l" name="926" href="#926">926</a>}                                   \
<a class="l" name="927" href="#927">927</a>                                    \
<a class="l" name="928" href="#928">928</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>void</b>                     \
<a class="l" name="929" href="#929">929</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_POISON&amp;project=OpenBSD">_RBT_POISON</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <b>unsigned</b> <b>long</b> <a href="/s?defs=poison&amp;project=OpenBSD">poison</a>)     \
<a class="hl" name="930" href="#930">930</a>{                                   \
<a class="l" name="931" href="#931">931</a>    <b>return</b> <a href="/s?defs=_rb_poison&amp;project=OpenBSD">_rb_poison</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=poison&amp;project=OpenBSD">poison</a>);       \
<a class="l" name="932" href="#932">932</a>}                                   \
<a class="l" name="933" href="#933">933</a>                                    \
<a class="l" name="934" href="#934">934</a><a href="/s?defs=__unused&amp;project=OpenBSD">__unused</a> <b>static</b> <b>inline</b> <b>int</b>                      \
<a class="l" name="935" href="#935">935</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_CHECK&amp;project=OpenBSD">_RBT_CHECK</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *<a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <b>unsigned</b> <b>long</b> <a href="/s?defs=poison&amp;project=OpenBSD">poison</a>)      \
<a class="l" name="936" href="#936">936</a>{                                   \
<a class="l" name="937" href="#937">937</a>    <b>return</b> <a href="/s?defs=_rb_check&amp;project=OpenBSD">_rb_check</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a>, <a href="/s?defs=elm&amp;project=OpenBSD">elm</a>, <a href="/s?defs=poison&amp;project=OpenBSD">poison</a>);        \
<a class="l" name="938" href="#938">938</a>}
<a class="l" name="939" href="#939">939</a>
<a class="hl" name="940" href="#940">940</a>#<b>define</b> <a class="xm" name="RBT_GENERATE_INTERNAL"/><a href="/s?refs=RBT_GENERATE_INTERNAL&amp;project=OpenBSD" class="xm">RBT_GENERATE_INTERNAL</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>, <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>, <a href="/s?defs=_aug&amp;project=OpenBSD">_aug</a>)     \
<a class="l" name="941" href="#941">941</a><b>static</b> <b>int</b>                              \
<a class="l" name="942" href="#942">942</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_COMPARE&amp;project=OpenBSD">_RBT_COMPARE</a>(<b>const</b> <b>void</b> *<a href="/s?defs=lptr&amp;project=OpenBSD">lptr</a>, <b>const</b> <b>void</b> *<a href="/s?defs=rptr&amp;project=OpenBSD">rptr</a>)         \
<a class="l" name="943" href="#943">943</a>{                                   \
<a class="l" name="944" href="#944">944</a>    <b>const</b> <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *l = <a href="/s?defs=lptr&amp;project=OpenBSD">lptr</a>, *r = <a href="/s?defs=rptr&amp;project=OpenBSD">rptr</a>;            \
<a class="l" name="945" href="#945">945</a>    <b>return</b> <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>(l, r);                      \
<a class="l" name="946" href="#946">946</a>}                                   \
<a class="l" name="947" href="#947">947</a><b>static</b> <b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_INFO&amp;project=OpenBSD">_RBT_INFO</a> = {            \
<a class="l" name="948" href="#948">948</a>    <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_COMPARE&amp;project=OpenBSD">_RBT_COMPARE</a>,                        \
<a class="l" name="949" href="#949">949</a>    <a href="/s?defs=_aug&amp;project=OpenBSD">_aug</a>,                               \
<a class="hl" name="950" href="#950">950</a>    <a href="/s?defs=offsetof&amp;project=OpenBSD">offsetof</a>(<b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>),                 \
<a class="l" name="951" href="#951">951</a>};                                  \
<a class="l" name="952" href="#952">952</a><b>const</b> <b>struct</b> <a class="d" href="#rb_type">rb_type</a> *<b>const</b> <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_TYPE&amp;project=OpenBSD">_RBT_TYPE</a> = &amp;<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_INFO&amp;project=OpenBSD">_RBT_INFO</a>
<a class="l" name="953" href="#953">953</a>
<a class="l" name="954" href="#954">954</a>#<b>define</b> <a class="xm" name="RBT_GENERATE_AUGMENT"/><a href="/s?refs=RBT_GENERATE_AUGMENT&amp;project=OpenBSD" class="xm">RBT_GENERATE_AUGMENT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>, <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>, <a href="/s?defs=_aug&amp;project=OpenBSD">_aug</a>)      \
<a class="l" name="955" href="#955">955</a><b>static</b> <b>void</b>                             \
<a class="l" name="956" href="#956">956</a><a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_AUGMENT&amp;project=OpenBSD">_RBT_AUGMENT</a>(<b>void</b> *<a href="/s?defs=ptr&amp;project=OpenBSD">ptr</a>)                      \
<a class="l" name="957" href="#957">957</a>{                                   \
<a class="l" name="958" href="#958">958</a>    <b>struct</b> <a href="/s?defs=_type&amp;project=OpenBSD">_type</a> *p = <a href="/s?defs=ptr&amp;project=OpenBSD">ptr</a>;                      \
<a class="l" name="959" href="#959">959</a>    <b>return</b> <a href="/s?defs=_aug&amp;project=OpenBSD">_aug</a>(p);                         \
<a class="hl" name="960" href="#960">960</a>}                                   \
<a class="l" name="961" href="#961">961</a><a class="d" href="#RBT_GENERATE_INTERNAL">RBT_GENERATE_INTERNAL</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>, <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>, <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_AUGMENT&amp;project=OpenBSD">_RBT_AUGMENT</a>)
<a class="l" name="962" href="#962">962</a>
<a class="l" name="963" href="#963">963</a>#<b>define</b> <a class="xm" name="RBT_GENERATE"/><a href="/s?refs=RBT_GENERATE&amp;project=OpenBSD" class="xm">RBT_GENERATE</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>, <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>)            \
<a class="l" name="964" href="#964">964</a>    <a class="d" href="#RBT_GENERATE_INTERNAL">RBT_GENERATE_INTERNAL</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_type&amp;project=OpenBSD">_type</a>, <a href="/s?defs=_field&amp;project=OpenBSD">_field</a>, <a href="/s?defs=_cmp&amp;project=OpenBSD">_cmp</a>, <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>)
<a class="l" name="965" href="#965">965</a>
<a class="l" name="966" href="#966">966</a>#<b>define</b> <a class="xm" name="RBT_INIT"/><a href="/s?refs=RBT_INIT&amp;project=OpenBSD" class="xm">RBT_INIT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)      <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_INIT&amp;project=OpenBSD">_RBT_INIT</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)
<a class="l" name="967" href="#967">967</a>#<b>define</b> <a class="xm" name="RBT_INSERT"/><a href="/s?refs=RBT_INSERT&amp;project=OpenBSD" class="xm">RBT_INSERT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)  <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_INSERT&amp;project=OpenBSD">_RBT_INSERT</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="l" name="968" href="#968">968</a>#<b>define</b> <a class="xm" name="RBT_REMOVE"/><a href="/s?refs=RBT_REMOVE&amp;project=OpenBSD" class="xm">RBT_REMOVE</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)  <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_REMOVE&amp;project=OpenBSD">_RBT_REMOVE</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="l" name="969" href="#969">969</a>#<b>define</b> <a class="xm" name="RBT_FIND"/><a href="/s?refs=RBT_FIND&amp;project=OpenBSD" class="xm">RBT_FIND</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_key&amp;project=OpenBSD">_key</a>)    <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_FIND&amp;project=OpenBSD">_RBT_FIND</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_key&amp;project=OpenBSD">_key</a>)
<a class="hl" name="970" href="#970">970</a>#<b>define</b> <a class="xm" name="RBT_NFIND"/><a href="/s?refs=RBT_NFIND&amp;project=OpenBSD" class="xm">RBT_NFIND</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_key&amp;project=OpenBSD">_key</a>)   <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_NFIND&amp;project=OpenBSD">_RBT_NFIND</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_key&amp;project=OpenBSD">_key</a>)
<a class="l" name="971" href="#971">971</a>#<b>define</b> <a class="xm" name="RBT_ROOT"/><a href="/s?refs=RBT_ROOT&amp;project=OpenBSD" class="xm">RBT_ROOT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)      <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_ROOT&amp;project=OpenBSD">_RBT_ROOT</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)
<a class="l" name="972" href="#972">972</a>#<b>define</b> <a class="xm" name="RBT_EMPTY"/><a href="/s?refs=RBT_EMPTY&amp;project=OpenBSD" class="xm">RBT_EMPTY</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)     <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_EMPTY&amp;project=OpenBSD">_RBT_EMPTY</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)
<a class="l" name="973" href="#973">973</a>#<b>define</b> <a class="xm" name="RBT_MIN"/><a href="/s?refs=RBT_MIN&amp;project=OpenBSD" class="xm">RBT_MIN</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)       <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_MIN&amp;project=OpenBSD">_RBT_MIN</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)
<a class="l" name="974" href="#974">974</a>#<b>define</b> <a class="xm" name="RBT_MAX"/><a href="/s?refs=RBT_MAX&amp;project=OpenBSD" class="xm">RBT_MAX</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)       <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_MAX&amp;project=OpenBSD">_RBT_MAX</a>(<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)
<a class="l" name="975" href="#975">975</a>#<b>define</b> <a class="xm" name="RBT_NEXT"/><a href="/s?refs=RBT_NEXT&amp;project=OpenBSD" class="xm">RBT_NEXT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)       <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_NEXT&amp;project=OpenBSD">_RBT_NEXT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="l" name="976" href="#976">976</a>#<b>define</b> <a class="xm" name="RBT_PREV"/><a href="/s?refs=RBT_PREV&amp;project=OpenBSD" class="xm">RBT_PREV</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)       <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_PREV&amp;project=OpenBSD">_RBT_PREV</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="l" name="977" href="#977">977</a>#<b>define</b> <a class="xm" name="RBT_LEFT"/><a href="/s?refs=RBT_LEFT&amp;project=OpenBSD" class="xm">RBT_LEFT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)       <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_LEFT&amp;project=OpenBSD">_RBT_LEFT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="l" name="978" href="#978">978</a>#<b>define</b> <a class="xm" name="RBT_RIGHT"/><a href="/s?refs=RBT_RIGHT&amp;project=OpenBSD" class="xm">RBT_RIGHT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)      <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_RIGHT&amp;project=OpenBSD">_RBT_RIGHT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="l" name="979" href="#979">979</a>#<b>define</b> <a class="xm" name="RBT_PARENT"/><a href="/s?refs=RBT_PARENT&amp;project=OpenBSD" class="xm">RBT_PARENT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)     <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_PARENT&amp;project=OpenBSD">_RBT_PARENT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>)
<a class="hl" name="980" href="#980">980</a>#<b>define</b> <a class="xm" name="RBT_SET_LEFT"/><a href="/s?refs=RBT_SET_LEFT&amp;project=OpenBSD" class="xm">RBT_SET_LEFT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_l&amp;project=OpenBSD">_l</a>)   <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_SET_LEFT&amp;project=OpenBSD">_RBT_SET_LEFT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_l&amp;project=OpenBSD">_l</a>)
<a class="l" name="981" href="#981">981</a>#<b>define</b> <a class="xm" name="RBT_SET_RIGHT"/><a href="/s?refs=RBT_SET_RIGHT&amp;project=OpenBSD" class="xm">RBT_SET_RIGHT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_r&amp;project=OpenBSD">_r</a>)  <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_SET_RIGHT&amp;project=OpenBSD">_RBT_SET_RIGHT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_r&amp;project=OpenBSD">_r</a>)
<a class="l" name="982" href="#982">982</a>#<b>define</b> <a class="xm" name="RBT_SET_PARENT"/><a href="/s?refs=RBT_SET_PARENT&amp;project=OpenBSD" class="xm">RBT_SET_PARENT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_p&amp;project=OpenBSD">_p</a>) <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_SET_PARENT&amp;project=OpenBSD">_RBT_SET_PARENT</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_p&amp;project=OpenBSD">_p</a>)
<a class="l" name="983" href="#983">983</a>#<b>define</b> <a class="xm" name="RBT_POISON"/><a href="/s?refs=RBT_POISON&amp;project=OpenBSD" class="xm">RBT_POISON</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_p&amp;project=OpenBSD">_p</a>) <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_POISON&amp;project=OpenBSD">_RBT_POISON</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_p&amp;project=OpenBSD">_p</a>)
<a class="l" name="984" href="#984">984</a>#<b>define</b> <a class="xm" name="RBT_CHECK"/><a href="/s?refs=RBT_CHECK&amp;project=OpenBSD" class="xm">RBT_CHECK</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_p&amp;project=OpenBSD">_p</a>)  <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>##<a href="/s?defs=_RBT_CHECK&amp;project=OpenBSD">_RBT_CHECK</a>(<a href="/s?defs=_elm&amp;project=OpenBSD">_elm</a>, <a href="/s?defs=_p&amp;project=OpenBSD">_p</a>)
<a class="l" name="985" href="#985">985</a>
<a class="l" name="986" href="#986">986</a>#<b>define</b> <a class="xm" name="RBT_FOREACH"/><a href="/s?refs=RBT_FOREACH&amp;project=OpenBSD" class="xm">RBT_FOREACH</a>(<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>, <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)                   \
<a class="l" name="987" href="#987">987</a>    <b>for</b> ((<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = <a class="d" href="#RBT_MIN">RBT_MIN</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>));                \
<a class="l" name="988" href="#988">988</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                      \
<a class="l" name="989" href="#989">989</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = <a class="d" href="#RBT_NEXT">RBT_NEXT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>)))
<a class="hl" name="990" href="#990">990</a>
<a class="l" name="991" href="#991">991</a>#<b>define</b> <a class="xm" name="RBT_FOREACH_SAFE"/><a href="/s?refs=RBT_FOREACH_SAFE&amp;project=OpenBSD" class="xm">RBT_FOREACH_SAFE</a>(<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>, <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_n&amp;project=OpenBSD">_n</a>)              \
<a class="l" name="992" href="#992">992</a>    <b>for</b> ((<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = <a class="d" href="#RBT_MIN">RBT_MIN</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>));                \
<a class="l" name="993" href="#993">993</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> &amp;&amp; ((<a href="/s?defs=_n&amp;project=OpenBSD">_n</a>) = <a class="d" href="#RBT_NEXT">RBT_NEXT</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>)), <span class="n">1</span>); \
<a class="l" name="994" href="#994">994</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = (<a href="/s?defs=_n&amp;project=OpenBSD">_n</a>))
<a class="l" name="995" href="#995">995</a>
<a class="l" name="996" href="#996">996</a>#<b>define</b> <a class="xm" name="RBT_FOREACH_REVERSE"/><a href="/s?refs=RBT_FOREACH_REVERSE&amp;project=OpenBSD" class="xm">RBT_FOREACH_REVERSE</a>(<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>, <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>)               \
<a class="l" name="997" href="#997">997</a>    <b>for</b> ((<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = <a class="d" href="#RBT_MAX">RBT_MAX</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>));                \
<a class="l" name="998" href="#998">998</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a>;                      \
<a class="l" name="999" href="#999">999</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = <a class="d" href="#RBT_PREV">RBT_PREV</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>)))
<a class="hl" name="1000" href="#1000">1000</a>
<a class="l" name="1001" href="#1001">1001</a>#<b>define</b> <a class="xm" name="RBT_FOREACH_REVERSE_SAFE"/><a href="/s?refs=RBT_FOREACH_REVERSE_SAFE&amp;project=OpenBSD" class="xm">RBT_FOREACH_REVERSE_SAFE</a>(<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>, <a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, <a href="/s?defs=_head&amp;project=OpenBSD">_head</a>, <a href="/s?defs=_n&amp;project=OpenBSD">_n</a>)          \
<a class="l" name="1002" href="#1002">1002</a>    <b>for</b> ((<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = <a class="d" href="#RBT_MAX">RBT_MAX</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_head&amp;project=OpenBSD">_head</a>));                \
<a class="l" name="1003" href="#1003">1003</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) != <a href="/s?defs=NULL&amp;project=OpenBSD">NULL</a> &amp;&amp; ((<a href="/s?defs=_n&amp;project=OpenBSD">_n</a>) = <a class="d" href="#RBT_PREV">RBT_PREV</a>(<a href="/s?defs=_name&amp;project=OpenBSD">_name</a>, (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>)), <span class="n">1</span>); \
<a class="l" name="1004" href="#1004">1004</a>         (<a href="/s?defs=_e&amp;project=OpenBSD">_e</a>) = (<a href="/s?defs=_n&amp;project=OpenBSD">_n</a>))
<a class="l" name="1005" href="#1005">1005</a>
<a class="l" name="1006" href="#1006">1006</a>#<b>endif</b>  <span class="c">/* _SYS_TREE_H_ */</span>
<a class="l" name="1007" href="#1007">1007</a></pre>
</div>
    <div id="footer">
<p><a href="http://www.opensolaris.org/os/project/opengrok/"
 title="Served by OpenGrok"><span id="fti"></span></a></p>
<div><img src="//mc.yandex.ru/watch/21237232" style="position:absolute; left:-9999px;" alt="" /></div>
<p>Indexes created Wed Jan 01 03:58:27 PST 2020</p></div></div>
</div>
</body>
</html>

