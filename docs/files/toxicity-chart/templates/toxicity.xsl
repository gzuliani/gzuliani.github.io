<?xml version="1.0" encoding="us-ascii"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD XHTML 1.0 Strict//EN" doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd" omit-xml-declaration="yes"/>

<xsl:variable name="max-toxicity">
 <xsl:for-each select="/toxicity/files/file/@toxicity">
  <xsl:sort data-type="number" order="descending"/>
  <xsl:if test="position() = 1">
   <xsl:value-of select="."/>
  </xsl:if>
 </xsl:for-each>
</xsl:variable>

<xsl:template match="toxicity">

 <html>
  <head>
   <link rel='stylesheet' type='text/css' href='toxicity.css'></link>
  </head>
  <body>

   <h1>
    <xsl:text>Toxicity Chart</xsl:text>
    <xsl:if test="@project-name != ''">
     <xsl:text> - </xsl:text>
     <xsl:value-of select="@project-name"/>
     <xsl:if test="@project-version != ''">
      <xsl:text> v. </xsl:text>
      <xsl:value-of select="@project-version"/>
     </xsl:if>
    </xsl:if>
   </h1>
   <xsl:if test="@date != ''">
    <p class="date">
     <xsl:text>Date: </xsl:text>
     <xsl:value-of select="@date"/>
    </p>
   </xsl:if>
   <xsl:if test="@tool != ''">
    <p class="tool">
     <xsl:text>Source: </xsl:text>
     <xsl:value-of select="@tool"/>
    </p>
   </xsl:if>

   <xsl:apply-templates select="files"/>
   <br/>

   <!-- legend -->
   <br/>
   <table class="legend" cellpadding="0" cellspacing="0">
    <tr>
     <td class="legend-caption">Legend:</td>
      <xsl:for-each select="thresholds/threshold/@metric">
       <xsl:element name="td">
        <xsl:attribute name="class">
         <xsl:value-of select="."/>
        </xsl:attribute>
       </xsl:element>
       <td class="ratio-undef"></td>
       <td class="legend">
        <xsl:value-of select="translate(., '-', ' ')"/>
       </td>
      </xsl:for-each>
    </tr>
   </table>

   <h2>Thresholds</h2>
   <xsl:apply-templates select="thresholds"/>
   <br/>

   <h2>Details</h2>
    <xsl:apply-templates select="files" mode="details"/>
   <br/>

  </body>
 </html>
</xsl:template>

<xsl:template match="files">
  <table class="toxicity" cellpadding="0" cellspacing="0">
   <tr>
    <th class="path">File</th>
    <th class="toxicity">Toxicity</th>
   </tr>
   <xsl:apply-templates select="file"/>
  </table>
</xsl:template>

<xsl:template match="file">
 <tr>
  <td class="path">
   <xsl:element name="a">
    <xsl:attribute name="name">
     <xsl:text>chart-</xsl:text>
     <xsl:value-of select="position()"/>
    </xsl:attribute>
   </xsl:element>
   <xsl:element name="a">
    <xsl:attribute name="href">
     <xsl:text>#detail-</xsl:text>
     <xsl:value-of select="position()"/>
    </xsl:attribute>
    <xsl:value-of select="@path"/>
   </xsl:element>
  </td>
  <td class="toxicity">
   <xsl:value-of select="format-number(@toxicity, '#.0')"/>
  </td>
 </tr>
 <tr class="bar">
  <td>
   <xsl:apply-templates select="./*"/>
  </td>
 </tr>
</xsl:template>

<xsl:template match="file/*">
 <xsl:element name="div">
  <xsl:attribute name="title">
   <xsl:value-of select="local-name()"/>
   <xsl:text>: </xsl:text>
   <xsl:value-of select="format-number(@toxicity, '#.0')"/>
  </xsl:attribute>
  <xsl:attribute name="class">
   <xsl:value-of select="local-name()"/>
  </xsl:attribute>
  <xsl:attribute name="style">
   <xsl:text>width:</xsl:text>
   <xsl:value-of select="@toxicity * 100 div $max-toxicity"/>
   <xsl:text>%</xsl:text>
  </xsl:attribute>
 </xsl:element>
</xsl:template>

<xsl:template match="thresholds">
 <table class="thresholds" cellpadding="0" cellspacing="0">
  <tr>
   <th class="thresholds">Metric</th>
   <th class="thresholds">Level</th>
   <th class="thresholds">Threshold</th>
  </tr>
  <xsl:apply-templates select="threshold"/>
 </table>
</xsl:template>

<xsl:template match="threshold">
  <tr>
   <td class="threshold-name"><xsl:value-of select="@metric"/></td>
   <td class="threshold-level"><xsl:value-of select="@level"/></td>
   <td class="threshold-value"><xsl:value-of select="@value"/></td>
  </tr>
</xsl:template>

<xsl:template match="files" mode="details">
 <table cellpadding="0" cellspacing="0" class="details">
  <xsl:apply-templates select="./*" mode="details"/>
 </table>
 <br/>
</xsl:template>

<xsl:template match="file" mode="details">
 <tr>
  <xsl:element name="td">
   <xsl:attribute name="colspan">2</xsl:attribute>
   <xsl:attribute name="class">
    <xsl:choose>
     <xsl:when test="position() = 1">
      <xsl:text>details-file-first</xsl:text>
     </xsl:when>
     <xsl:otherwise>
      <xsl:text>details-file</xsl:text>
     </xsl:otherwise>
    </xsl:choose>
   </xsl:attribute>
   <xsl:element name="a">
    <xsl:attribute name="name">
     <xsl:text>detail-</xsl:text>
     <xsl:value-of select="position()"/>
    </xsl:attribute>
   </xsl:element>
    <xsl:value-of select="@path"/>
  </xsl:element>
 </tr>
 <xsl:apply-templates select="./*" mode="details"/>
 <tr>
  <td class="top" colspan="2">
   <xsl:element name="a">
    <xsl:attribute name="href">
     <xsl:text>#chart-</xsl:text>
     <xsl:value-of select="position()"/>
    </xsl:attribute>
    <xsl:text>return to chart</xsl:text>
   </xsl:element>
  </td>
 </tr>
</xsl:template>

<xsl:template match="file/*" mode="details">
 <xsl:variable name="metric-name" select="local-name()" />
 <xsl:choose>
  <xsl:when test="count(./*) &gt; 0">
   <tr>
    <td class="details-metric" colspan="2">
     <xsl:value-of select="$metric-name"/>
     <xsl:text> (max. </xsl:text>
     <xsl:value-of select="/toxicity/thresholds/threshold[@metric=$metric-name]/@value"/>
     <xsl:text>)</xsl:text>
    </td>
   </tr>
   <xsl:apply-templates select="method" mode="details">
    <xsl:sort select="@value" data-type="number" order="descending"></xsl:sort>
   </xsl:apply-templates>
  </xsl:when>
  <xsl:when test="@toxicity &gt; 0">
   <tr>
    <td class="details-metric">
     <xsl:value-of select="$metric-name"/>
     <xsl:text> (max. </xsl:text>
     <xsl:value-of select="/toxicity/thresholds/threshold[@metric=$metric-name]/@value"/>
     <xsl:text>)</xsl:text>
    </td>
    <td class="details-value">
     <xsl:value-of select="@value"/>
    </td>
   </tr>
  </xsl:when>
 </xsl:choose>
</xsl:template>

<xsl:template match="method" mode="details">
 <xsl:element name="tr">
  <xsl:attribute name="class">
   <xsl:choose>
    <xsl:when test="position() mod 2=1">
       <xsl:text>detail-even</xsl:text>
    </xsl:when>
    <xsl:otherwise>
       <xsl:text>detail-odd</xsl:text>
    </xsl:otherwise>
   </xsl:choose>
  </xsl:attribute>
  <td class="details-label">
   <xsl:value-of select="@name"/>
  </td>
  <td class="details-value">
   <xsl:value-of select="@value"/>
  </td>
 </xsl:element>
</xsl:template>

</xsl:stylesheet>
