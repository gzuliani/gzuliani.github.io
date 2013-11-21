<?xml version="1.0" encoding="us-ascii"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd" omit-xml-declaration="yes"/>

<xsl:template match="pyramid">

 <!-- metrics -->
 <xsl:variable name="andc"             select="andc"/>
 <xsl:variable name="ahh"              select="ahh"/>
 <xsl:variable name="nop"              select="nop"/>
 <xsl:variable name="noc"              select="noc"/>
 <xsl:variable name="nom"              select="nom"/>
 <xsl:variable name="loc"              select="loc"/>
 <xsl:variable name="cyclo"            select="cyclo"/>
 <xsl:variable name="calls"            select="calls"/>
 <xsl:variable name="fanout"           select="fanout"/>

 <!-- ratios -->
 <xsl:variable name="noc_nop" select="$noc div $nop"/>
 <xsl:variable name="nom_noc" select="$nom div $noc"/>
 <xsl:variable name="loc_nom" select="$loc div $nom"/>
 <xsl:variable name="calls_nom" select="$calls div $nom"/>
 <xsl:variable name="cyclo_loc" select="$cyclo div $loc"/>
 <xsl:variable name="fanout_calls" select="$fanout div $calls"/>

 <!-- thresholds (c++) -->
 <xsl:variable name="min_andc"         select=" 0.19"/>
 <xsl:variable name="max_andc"         select=" 0.37"/>
 <xsl:variable name="min_ahh"          select=" 0.05"/>
 <xsl:variable name="max_ahh"          select=" 0.21"/>
 <xsl:variable name="min_noc_nop"      select=" 3.00"/>
 <xsl:variable name="max_noc_nop"      select="35.00"/>
 <xsl:variable name="min_nom_noc"      select=" 4.00"/>
 <xsl:variable name="max_nom_noc"      select="15.00"/>
 <xsl:variable name="min_loc_nom"      select=" 5.00"/>
 <xsl:variable name="max_loc_nom"      select="16.00"/>
 <xsl:variable name="min_cyclo_loc"    select=" 0.20"/>
 <xsl:variable name="max_cyclo_loc"    select=" 0.30"/>
 <xsl:variable name="min_calls_nom"    select=" 1.17"/>
 <xsl:variable name="max_calls_nom"    select=" 2.00"/>
 <xsl:variable name="min_fanout_calls" select=" 0.20"/>
 <xsl:variable name="max_fanout_calls" select=" 0.48"/>

 <html>
  <head>
   <link rel='stylesheet' type='text/css' href='pyramid.css'></link>
  </head>
  <body>

  <h1>Overview Pyramid</h1>
  <p class="source">Source: <xsl:value-of select="@tool"/></p>
  <br/>
  <table class="pyramid" cellpadding="0" cellspacing="0" boder="1">
   <tr>
    <td class="outer" colspan="4"></td>
    <td class="inheritance-label">ANDC</td>
    <td class="inheritance-inner"></td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($andc)!=$andc"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$andc &lt; $min_andc"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$andc &gt; $max_andc"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($andc)=$andc"><xsl:value-of select="format-number($andc, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="outer" colspan="4"></td>
   </tr>
   <tr>
    <td class="outer" colspan="4"></td>
    <td class="inheritance-label">AHH</td>
    <td class="inheritance-inner"></td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($ahh)!=$ahh"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$ahh &lt; $min_ahh"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$ahh &gt; $max_ahh"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($ahh)=$ahh"><xsl:value-of select="format-number($ahh, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="outer" colspan="4"></td>
   </tr>
   <tr>
    <td class="outer" colspan="3"></td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($noc_nop)!=$noc_nop"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$noc_nop &lt; $min_noc_nop"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$noc_nop &gt; $max_noc_nop"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($noc_nop)=$noc_nop"><xsl:value-of select="format-number($noc_nop, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="size-and-complexity-label">NOP</td>
    <td class="size-and-complexity-inner"></td>
    <td class="size-and-complexity-value">
     <xsl:choose>
      <xsl:when test="$nop=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$nop"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="outer" colspan="4"></td>
   </tr>
   <tr>
    <td class="outer" colspan="2"></td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($nom_noc)!=$nom_noc"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$nom_noc &lt; $min_nom_noc"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$nom_noc &gt; $max_nom_noc"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($nom_noc)=$nom_noc"><xsl:value-of select="format-number($nom_noc, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="size-and-complexity-label">NOC</td>
    <td class="size-and-complexity-inner" colspan="2"></td>
    <td class="size-and-complexity-value">
     <xsl:choose>
      <xsl:when test="$noc=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$noc"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="outer" colspan="4"></td>
   </tr>
   <tr>
    <td class="outer"></td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($loc_nom)!=$loc_nom"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$loc_nom &lt; $min_loc_nom"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$loc_nom &gt; $max_loc_nom"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($loc_nom)=$loc_nom"><xsl:value-of select="format-number($loc_nom, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="size-and-complexity-label">NOM</td>
    <td class="size-and-complexity-inner" colspan="3"></td>
    <td class="size-and-complexity-value">
     <xsl:choose>
      <xsl:when test="$nom=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$nom"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="coupling-value"></td>
    <td class="coupling-label">NOM</td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($calls_nom)!=$calls_nom"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$calls_nom &lt; $min_calls_nom"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$calls_nom &gt; $max_calls_nom"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($calls_nom)=$calls_nom"><xsl:value-of select="format-number($calls_nom, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="outer"></td>
   </tr>
   <tr>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($cyclo_loc)!=$cyclo_loc"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$cyclo_loc &lt; $min_cyclo_loc"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$cyclo_loc &gt; $max_cyclo_loc"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($cyclo_loc)=$cyclo_loc"><xsl:value-of select="format-number($cyclo_loc, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
    <td class="size-and-complexity-label">LOC</td>
    <td class="size-and-complexity-inner" colspan="4"></td>
    <td class="size-and-complexity-value">
     <xsl:choose>
      <xsl:when test="$loc=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$loc"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="coupling-value">
     <xsl:choose>
      <xsl:when test="$calls=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$calls"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="coupling-inner"></td>
    <td class="coupling-label">CALLS</td>
    <xsl:element name="td">
     <xsl:attribute name="class">
      <xsl:choose>
       <xsl:when test="number($fanout_calls)!=$fanout_calls"><xsl:text>ratio-undef</xsl:text></xsl:when>
       <xsl:when test="$fanout_calls &lt; $min_fanout_calls"><xsl:text>ratio-low</xsl:text></xsl:when>
       <xsl:when test="$fanout_calls &gt; $max_fanout_calls"><xsl:text>ratio-high</xsl:text></xsl:when>
       <xsl:otherwise><xsl:text>ratio-ok</xsl:text></xsl:otherwise>
      </xsl:choose>
     </xsl:attribute>
     <xsl:choose>
      <xsl:when test="number($fanout_calls)=$fanout_calls"><xsl:value-of select="format-number($fanout_calls, '#.0')"/></xsl:when>
      <xsl:otherwise><xsl:text>n/a</xsl:text></xsl:otherwise>
     </xsl:choose>
    </xsl:element>
   </tr>
   <tr>
    <td class="size-and-complexity-label">CYCLO</td>
    <td class="size-and-complexity-inner" colspan="5"></td>
    <td class="size-and-complexity-value">
     <xsl:choose>
      <xsl:when test="$cyclo=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$cyclo"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="coupling-value">
     <xsl:choose>
      <xsl:when test="$fanout=''"><xsl:text>n/a</xsl:text></xsl:when>
      <xsl:otherwise><xsl:value-of select="$fanout"/></xsl:otherwise>
     </xsl:choose>
    </td>
    <td class="coupling-inner" colspan="2"></td>
    <td class="coupling-label">FANOUT</td>
   </tr>
  </table>

  <!-- legend -->
  <br/>
  <table class="legend" cellpadding="0" cellspacing="0">
   <tr>
    <td class="legend-caption">Legend:</td>
    <td class="ratio-undef"></td>
    <td class="legend">undefined</td>
    <td class="ratio-ok"></td>
    <td class="legend">value in range</td>
    <td class="ratio-low"></td>
    <td class="legend">value too small</td>
    <td class="ratio-high"></td>
    <td class="legend">value too big</td>
   </tr>
  </table>

  <h2>Thresholds</h2>
   <table class="thresholds" cellpadding="0" cellspacing="0">
    <tr><th>Value</th><th>Low</th><th>High</th></tr>
    <tr>
     <td class="thresholds-value">ANDC</td>
     <td class="thresholds-low"><xsl:value-of select="$min_andc"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_andc"/></td>
    </tr>
    <tr>
     <td class="thresholds-value">AHH</td>
     <td class="thresholds-low"><xsl:value-of select="$min_ahh"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_ahh"/></td>
    </tr>
    <tr>
     <td class="thresholds-value">NOM/NOC</td>
     <td class="thresholds-low"><xsl:value-of select="$min_nom_noc"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_nom_noc"/></td>
    </tr>
    <tr>
     <td class="thresholds-value">LOC/NOM</td>
     <td class="thresholds-low"><xsl:value-of select="$min_loc_nom"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_loc_nom"/></td>
    </tr>
    <tr>
     <td class="thresholds-value">CYCLO/LOC</td>
     <td class="thresholds-low"><xsl:value-of select="$min_cyclo_loc"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_cyclo_loc"/></td>
    </tr>
    <tr>
     <td class="thresholds-value">CALLS/NOM</td>
     <td class="thresholds-low"><xsl:value-of select="$min_calls_nom"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_calls_nom"/></td>
    </tr>
    <tr>
     <td class="thresholds-value">FANOUT/CALLS</td>
     <td class="thresholds-low"><xsl:value-of select="$min_fanout_calls"/></td>
     <td class="thresholds-high"><xsl:value-of select="$max_fanout_calls"/></td>
    </tr>
   </table>

  <h2>Smells</h2>
  <ul>
  <xsl:choose>
   <xsl:when test="$andc &lt; $min_andc and $ahh &lt; $min_ahh">
    <li>ANDC and ANDC are low: class hierarchies are rather sparse, i.e. there are mostly standalone classes and few inheritance relations.</li>
   </xsl:when>
   <xsl:when test="$andc &lt; $min_andc">
    <li>ANDC is low: class hierarchies tend to be rather narrow, i.e. base-classes have few directly derived sub-classes.</li>
   </xsl:when>
   <xsl:when test="$andc &gt; $max_andc">
    <li>ANDC is high: class hierarchies tend to be rather wide, i.e. base-classes have many directly derived sub-classes.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$andc &lt; $min_andc and $ahh &lt; $min_ahh">
    <!-- already managed! -->
   </xsl:when>
   <xsl:when test="$ahh &lt; $min_ahh">
    <li>AHH is low: class hierarchies tend to be rather shallow, i.e. inheritance trees tend to have few depth levels.</li>
   </xsl:when>
   <xsl:when test="$ahh &gt; $max_ahh">
    <li>AHH is high: class hierarchies tend to be rather deep, i.e. inheritance trees tend to have many depth levels.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$noc_nop &lt; $min_noc_nop">
    <li>NOC/NOP is low: packages tend to be too fine-grained, i.e. they contain too few classes.</li>
   </xsl:when>
   <xsl:when test="$noc_nop &gt; $max_noc_nop">
    <li>NOC/NOP is high: packages tend to be too coarse-grained, i.e. they contain too many classes.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$nom_noc &lt; $min_nom_noc">
    <li>NOM/NOC is low: classes tend to be rather small, i.e. they have only few methods.</li>
   </xsl:when>
   <xsl:when test="$nom_noc &gt; $max_nom_noc">
    <li>NOM/NOC is high: classes tend to be rather big, i.e. they define many methods.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$loc_nom &lt; $min_loc_nom">
    <li>LOC/NOM is low: methods tend to be rather short.</li>
   </xsl:when>
   <xsl:when test="$loc_nom &gt; $max_loc_nom">
    <li>LOC/NOM is high: methods tend to be rather long.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$cyclo_loc &lt; $min_cyclo_loc">
    <li>CYCLO/LOC is low: methods tend to have a rather simple logic.</li>
   </xsl:when>
   <xsl:when test="$cyclo_loc &gt; $max_cyclo_loc">
    <li>CYCLO/LOC is high: methods tend to have a rather complex logic.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$calls_nom &lt; $min_calls_nom">
    <li>CALLS/NOM is low: methods tend to call few other methods.</li>
   </xsl:when>
   <xsl:when test="$calls_nom &gt; $max_calls_nom">
    <li>CALLS/NOM is high: methods tend to call many other methods.</li>
   </xsl:when>
  </xsl:choose>
  <xsl:choose>
   <xsl:when test="$fanout_calls &lt; $min_fanout_calls">
    <li>FANOUT/CALLS is low: methods tend to reference few other classes.</li>
   </xsl:when>
   <xsl:when test="$fanout_calls &gt; $max_fanout_calls">
    <li>FANOUT/CALLS is high: methods tend to reference many other classes.</li>
   </xsl:when>
  </xsl:choose>
  </ul>

  <h2>Explanation</h2>
  <p>A brief description of the metrics used in the <em>Overview Pyramid</em>.</p>
  <h3>Top part: System Inheritance</h3>
  <dl>
   <dt>ANDC</dt><dd>average number of derived classes;</dd>
   <dt>AHH</dt><dd>average hierarchy height.</dd>
  </dl>
  <h3>Left part: System Size and Complexity</h3>
  <h4>Direct metrics</h4>
  <dl>
   <dt>NOP</dt><dd>number of packages;</dd>
   <dt>NOC</dt><dd>number of classes;</dd>
   <dt>NOM</dt><dd>number of methods;</dd>
   <dt>LOC</dt><dd>lines of code;</dd>
   <dt>CYCLO</dt><dd>cyclomatic complexity index.</dd>
  </dl>
  <h4>Derived metrics</h4>
  <dl>
   <dt>NOC/NOP</dt><dd>average number of classes per package &#x2192; high-level structuring, indicates if packages tend to be coarse or fine grained;</dd>
   <dt>NOM/NOC</dt><dd>average number of methods per class &#x2192; class structuring, indicates how operations are distributed over the system;</dd>
   <dt>LOC/NOM</dt><dd>average number of lines per method &#x2192; operation structuring, indicates how well the system's behaviuor is distributed over operations;</dd>
   <dt>CYCLO/LOC</dt><dd>average method complexity &#x2192; intrinsic operation complexity, indicates the expected complexity of an operation.</dd>
  </dl>
  <h3>Right part: System Coupling</h3>
  <h4>Direct metrics</h4>
  <dl>
   <dt>CALLS</dt><dd>number of calls;</dd>
   <dt>FANOUT</dt><dd>number of referenced types.</dd>
  </dl>
  <h4>Derived metrics</h4>
  <dl>
   <dt>CALLS/NOM</dt><dd>average number of calls in a method &#x2192; coupling intensity, indicates how many operations are invoked on average by each operation;</dd>
   <dt>FANOUT/CALLS</dt><dd>average number of external calls &#x2192; coupling dispersion, indicates how many classes are involved on average in a single operation.</dd>
  </dl>
 </body>
 </html>
</xsl:template>

</xsl:stylesheet>
