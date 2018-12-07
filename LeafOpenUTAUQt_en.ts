<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en" sourcelanguage="zh_CN">
<context>
    <name></name>
    <message>
        <source>输出的 .wav 文件的采样频率</source>
        <translation type="vanished">Sampling frequency of output .wav file</translation>
    </message>
    <message>
        <source>输出的 .wav 文件的位深</source>
        <translation type="vanished">Bit depth of output .wav file</translation>
    </message>
    <message>
        <source>开启时, 在resampler模式下生成 .wav 文件 （用于与其他wavtool兼容）。此选项将减慢合成。</source>
        <oldsource>开启时, 在resampler模式下生成 .wav 文件 （用于与其他wavtool兼容）。此选项将减慢合成。 </oldsource>
        <translation type="vanished">When turned on, generate .wav file in resampler mode (to be compatible with other wavtools); slows down synthesis。</translation>
    </message>
    <message>
        <source>对每个音符应用自适应增益，使得当音量为100％时，合成波形的峰值达到最大幅度的一半。full: 对浊音和清音均进行增益； voiced: 只增益浊音；off: 不改变音量。</source>
        <translation type="vanished">Apply an adaptive gain to each note such that the peak of synthesized waveform goes to half of the maximum amplitude when volume is 100%; full: gain both voiced and unvoiced parts; voiced: only gain voiced part; off: do not adjust volume. Example (full,voiced,off from top to bottom).</translation>
    </message>
    <message>
        <source>基于心理声学响度测量，在修改后使可感知响度保持。</source>
        <translation type="vanished">Retain the perceived loudness after modification, based on a psychoacoustic loudness measure. Example (off, on from top to bottom).</translation>
    </message>
    <message>
        <source>决定Moresampler如何使音符时间变长。auto: 根据源时长和目标时长自动决定是使用拉伸方式还是循环方式。可使用 e 和 Me flag 来覆盖这一行为。</source>
        <translation type="vanished">Determines how Moresampler extends the duration of each note; auto: automatically stretch or loop the note based on its original and target duration. The effect can be overwritten by e and Me flags.</translation>
    </message>
    <message>
        <source>on: wavtool模式下的合成将多线程运行（将会更快）。full: resampler模式也将在多线程运行。“多线程”意味着将多个线程包装于一个进程中，与同一时间运行多个Moresampler的“多进程”有着本质不同。注意，该特性不被 moresampler-legacy.exe支持。</source>
        <translation type="vanished">When turned on, the final synthesis stage in wavtool mode will run in multiple threads (which means faster). When set to &quot;full&quot;, resampler mode will also become multithreaded. &quot;multithread&quot;, which packs multiple threads into a process, is inherently different from &quot;multiprocess&quot; which launches multiple instances of Moresampler at a time. Note: this feature is not supported by moresampler-legacy.exe.</translation>
    </message>
    <message>
        <source>检查.wav 文件与对应.llsm 文件和mrq数据项的最后修改时间。如果.wav文件比.llsm要新，则进行重分析。若.wav文件也比mrq数据项要新，则在重分析以生成.llsm文件前进行音高重估计。此特性或许对声库开发者有帮助。</source>
        <oldsource>检查.wav 文件与对应.llsm 文件和mrq数据项的最后修改时间。如果.wav文件比.llsm要新，则进行重分析。若.wav文件也比mrq数据项要新，则在重分析以生成.llsm文件前进行音高重估计。此特性或许对声库开发者有帮助。 </oldsource>
        <translation type="vanished">Check the last modified time of .wav file and corresponding .llsm file and mrq data entry. If the .wav file is newer than the .llsm file, then reanalyze. If the .wav file is also newer than the mrq data entry, then reestimate pitch before reanalyzing .llsm. This feature might be helpful for voicebank developers.</translation>
    </message>
    <message>
        <source>在指定文件路径中输出Debug信息。</source>
        <translation type="vanished">Output debug information into a specified file path.</translation>
    </message>
    <message>
        <source>从文件夹名推测音高。例如，如果给定的样本位于一个名为“C_D4”的文件夹下，Moresampler将在接近D4的范围（294 Hz左右）内进行音高分析。</source>
        <translation type="vanished">Infer the pitch range from directory name. For example, if the given sample is under a directory named &quot;C_D4&quot;, Moresampler would run pitch analysis in a range close to D4 (around 294Hz).</translation>
    </message>
    <message>
        <source>在接合音高与浊音行为估计期间增大浊音化概率，随后进行浊音音高修正；旨在提高特异度和降低灵敏度；适用于嘈杂/粗糙的语音，但会降低干净/流畅语音的质量。</source>
        <oldsource>在接合音高与浊音行为估计期间增大浊音化概率，随后进行浊音音高修正；旨在提高特异度和降低灵敏度；适用于嘈杂/粗糙的语音，但会降低干净/流畅语音的质量。 </oldsource>
        <translation type="vanished">(over)Emphasize voicing probability during joint pitch &amp; voicing activity estimation, followed by a pitch &amp; voicing correction procedure; tend to reduce false negative but raise false positive rate; works for noisy/coarse speech but degrades the quality of clean/smooth speech.</translation>
    </message>
    <message>
        <source>音高的下界(以Hz为单位)。</source>
        <translation type="vanished">The lower bound for pitch (in Hz).</translation>
    </message>
    <message>
        <source>音高的上界(以Hz为单位)。</source>
        <translation type="vanished">The upper bound for pitch (in Hz).</translation>
    </message>
    <message>
        <source>strict : 当desc.mrq不可用时，从.frq 文件读取音高数据。on : 使用 .frq 文件的音高数据来修正Moresampler自己对音高的猜测。不管该选项是否开启，结果都会保存至desc.mrq。注意：除非被仔细修正，.frq文件提供的音高数据通常无法足够可靠地使Moresampler运作。</source>
        <translation type="vanished">When desc.mrq is not available, load pitch data from .frq file when set to strict; when set to on, use pitch data from .frq file to correct the pitch estimated by Moresampler&apos;s own estimator. No matter this option is turned on or not, the result will always be written into desc.mrq. Note: unless carefully corrected, pitch provided by .frq files are often not robust enough for Moresampler to run properly.</translation>
    </message>
    <message>
        <source>on : Moresampler将自动修复由噪声失真或低音量（量化误差）引起的分析错误。这些错误可能造成音高变换后的“尖锐”与“粗糙”的声音。然而此特性（理论上）可能导致轻微模糊。</source>
        <translation type="vanished">When turned on, Moresampler will automatically fix analysis inaccuracy caused by noise distortion or low volume (quantization error) which may result in &quot;sharp&quot;, &quot;gross&quot; voice after pitch shifting. However turning on this feature may (in theory) slightly blur the speech. Example (off, on from top to bottom).</translation>
    </message>
    <message>
        <source>在从.wav文件分析LLSM时自动降噪。更适用于长录音。</source>
        <translation type="vanished">Automatically reduces noise when analyzing LLSM from .wav; works better with longer recordings.</translation>
    </message>
    <message>
        <source>在分析时自动移除输入中存在的次谐波。对尖亮的声音可能有帮助，但会导致呼吸音的质量降低。</source>
        <translation type="vanished">Automatically remove the subharmonics (if there&apos;s any) from input speech during analysis. Might be helpful for screamy voices but slightly degrades the quality of breathy voices.</translation>
    </message>
</context>
<context>
    <name>AvailableTextCodecDialog</name>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="14"/>
        <source>支持的编码</source>
        <translation>Supported encoding</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;支持的编码：&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Supported encodings:&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="27"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;您可以通过在此处键入文本来搜索下面显示的字符编码。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;You can search for the character encoding shown below by typing text here.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="30"/>
        <source>键入以搜索</source>
        <translation>Type to search</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="43"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;此处显示Qt支持的文本编码的列表。您可以通过右键菜单复制它们其中的一个。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Here shows text encodings that Qt support. You can copy one of them by right-click menu. &lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="59"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;在Qt的内部实现中，以上的有些编码是同一种编码的别名。&lt;/p&gt;&lt;p&gt;您可以通过右键菜单来复制相应字符串到剪贴板，或者直接双击或选择后确定以应用至父窗口。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;In the internal implementation of Qt, some of the above encodings are aliases of the same encoding.&lt;/p&gt;&lt;p&gt;You can copy the corresponding string to the clipboard via the right-click menu, or double-click or select and click OK to apply to the parent window.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="79"/>
        <source>复制该编码名称</source>
        <translation>Copy the name of the encoding</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/availabletextcodecdialog.ui" line="82"/>
        <source>将选定的编码名称复制到剪贴板</source>
        <translation>Copy the selected encoding name to the clipboard</translation>
    </message>
</context>
<context>
    <name>CategoriesAndLabelsListWidget</name>
    <message>
        <location filename="VoiceBankUtils/categoriesandlabelslistwidget.ui" line="115"/>
        <source>分类</source>
        <translation>Categories</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/categoriesandlabelslistwidget.ui" line="150"/>
        <source>标签</source>
        <translation>Labels</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/categoriesandlabelslistwidget.cpp" line="176"/>
        <source>清除未使用的分类</source>
        <translation>Remove unused categories</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/categoriesandlabelslistwidget.cpp" line="186"/>
        <source>清除未使用的标签</source>
        <translation>Remove unused labels</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/categoriesandlabelslistwidget.cpp" line="206"/>
        <source>未分类</source>
        <translation>Uncategorized</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/categoriesandlabelslistwidget.cpp" line="225"/>
        <source>无标签</source>
        <translation>No labels</translation>
    </message>
</context>
<context>
    <name>CategoriesModel</name>
    <message>
        <location filename="VoiceBankUtils/categoriesmodel.cpp" line="26"/>
        <source>未分类 (%1)</source>
        <translation>Uncategorized (%1)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/categoriesmodel.cpp" line="28"/>
        <source>全部 (%1)</source>
        <translation>All (%1)</translation>
    </message>
</context>
<context>
    <name>EditorWindow</name>
    <message>
        <location filename="editorwindow.ui" line="13"/>
        <source>EditorWindow</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>ImageCropperContainer</name>
    <message>
        <location filename="../ImageCropper/src/imagecroppercontainer.ui" line="14"/>
        <source>Form</source>
        <translation></translation>
    </message>
</context>
<context>
    <name>LabelsModel</name>
    <message>
        <location filename="VoiceBankUtils/labelsmodel.cpp" line="27"/>
        <source>无标签 (%1)</source>
        <translation>No labels (%1)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/labelsmodel.cpp" line="29"/>
        <source>全部 (%1)</source>
        <translation>All (%1)</translation>
    </message>
</context>
<context>
    <name>MonitorFoldersAddDialog</name>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.ui" line="14"/>
        <source>添加一个监视文件夹</source>
        <translation>Add a watch folder</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.ui" line="20"/>
        <source>输入要添加的被监视文件夹路径，或者使用浏览：</source>
        <translation>Enter the path of the monitored folder you want to add, or use &quot;Browse&quot;:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.ui" line="34"/>
        <source>浏览</source>
        <translation>Browse</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfoldersadddialog.cpp" line="23"/>
        <source>选择一个文件夹</source>
        <translation>Choose a folder</translation>
    </message>
</context>
<context>
    <name>MonitorFoldersSettingDialog</name>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="14"/>
        <source>监视文件夹设定</source>
        <translation>Watch Folders Seetings</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="20"/>
        <source>添加</source>
        <translation>Add</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="27"/>
        <source>删除</source>
        <translation>Remove</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.ui" line="50"/>
        <source>监视文件夹列表：</source>
        <translation>Watch folders list:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="53"/>
        <source>路径不存在</source>
        <translation>Path not exists</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="53"/>
        <source>您输入的路径不存在。监视文件夹列表将不做更改。</source>
        <translation>The path you entered does not exist.The watch folder list will not be changed.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="56"/>
        <source>路径为空</source>
        <translation>Path is empty</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/monitorfolderssettingdialog.cpp" line="56"/>
        <source>您并没有输入路径。监视文件夹列表将不做更改。</source>
        <translation>You did not enter a path. The watch folder list will not be changed.</translation>
    </message>
</context>
<context>
    <name>MoresamplerConfig</name>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="41"/>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="42"/>
        <source>（空行）</source>
        <translation>(Empty line)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="48"/>
        <source>（注释）</source>
        <translation>(Comments)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="93"/>
        <source>分析配置</source>
        <translation>Analysis configuration</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="95"/>
        <source>元标记</source>
        <translation>Meta flags</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="97"/>
        <source>杂项</source>
        <translation>Miscellaneous configuration</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="99"/>
        <source>输出配置</source>
        <translation>Output configuration</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="101"/>
        <source>合成配置</source>
        <translation>Synthesis configuration</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="103"/>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="109"/>
        <source>未知</source>
        <translation>Unknown</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="105"/>
        <source>注释</source>
        <translation>Comments</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="107"/>
        <source>空行</source>
        <translation>Empty line</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="114"/>
        <source>（元标记）</source>
        <translation>(Meta flags)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="115"/>
        <source>元标记提供了一种快捷的方式让您多个flag合并为一个。元标记在全局配置文件中被定义,并通过 M+数字 (例如 M1, M2, M3) 的形式使用。通过在元标记之后放置点和数字，对应的 flag 的有效数值将按照数字缩放（以百分比表示，只要缩放的结果仍然在每个标志的允许范围内）。</source>
        <translation>meta flag offers a shortcut that you can combine multiple flags into one which saves effort when typing flag sequences in UTAU&apos;s note settings panel. Meta flags are defined in the global configuration file, and activated in the format M+number (e.g. M1, M2, M3). By putting dot and number after a meta flag, the effectiveness can be scaled by the number (as a percentage, as long as the result of scaling is still within the allowed range of each flag).</translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigAddNewDialog</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigaddnewdialog.ui" line="14"/>
        <source>添加一个新的Moresampler配置项</source>
        <translation>Add a new Moresampler configuration item</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigaddnewdialog.ui" line="20"/>
        <source>从下列配置项中选择一个来添加：</source>
        <translation>Choose one from below configuration items:</translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsAddNewModel</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="6"/>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="70"/>
        <source>（空行）</source>
        <translation>(Empty line)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="6"/>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="70"/>
        <source>（注释）</source>
        <translation>(Comments)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="8"/>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="72"/>
        <source>（元标记）</source>
        <translation>(Meta flags)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="29"/>
        <source>设置项</source>
        <translation>Config entry</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="31"/>
        <source>类型</source>
        <translation>Type</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="33"/>
        <source>说明</source>
        <translation>Note</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsaddnewmodel.cpp" line="73"/>
        <source>元标记</source>
        <translation>Meta flags</translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsDelegate</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="24"/>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="25"/>
        <source>是</source>
        <translation>Yes</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="24"/>
        <location filename="EngineUtils/moresamplerconfigsdelegate.cpp" line="25"/>
        <source>否</source>
        <translation>No</translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsDialog</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="20"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;您可以通过该按钮来删除当前选中的行。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;You can use this button to delete the currently selected line.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="23"/>
        <source>删除</source>
        <translation>Remove</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="53"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;您可以通过该按钮在文件的最后一行新建一个配置项。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;This button allows you to create a new configuration item on the last line of the file.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="56"/>
        <source>添加</source>
        <translation>Add</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.ui" line="63"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;这里显示配置文件中的配置项。&lt;/p&gt;&lt;p&gt;您可以双击“值”一列来编辑配置项的值。如果您编辑的是全局配置，您可以双击“是否覆盖声库配置”来选择是否覆盖各个声库中定义的配置。&lt;/p&gt;&lt;p&gt;若要添加和删除配置项，使用左下角的“添加”和“删除”按钮。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;This shows the configuration items in the configuration file.&lt;/p&gt;&lt;p&gt;You can double-click the Value column to edit the value of a configuration item. If you are editing a global configuration, you can double-click &quot;Overwrite voicebank configuration&quot; to choose whether to override the configuration defined in each voicebank.&lt;/p&gt;&lt;p&gt;To add and remove configuration items, use the Add and Remove buttons in the lower left corner.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="18"/>
        <source>编辑“%1”的Moresampler配置</source>
        <translation>Edit Moresampler configurations of &quot;%1&quot;</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="20"/>
        <source>编辑名称未知的音源的Moresampler配置</source>
        <oldsource>编辑名称位置的音源的Moresampler配置</oldsource>
        <translation>Edit the Moresampler configurationz for a voicebank whose name is unknown</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="23"/>
        <source>编辑全局Moresampler配置</source>
        <translation>Edit Global Moresampler Configurations</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="24"/>
        <source>当前正在编辑：%1</source>
        <translation>Currently editing:%1</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="41"/>
        <source>没有可删除的项</source>
        <translation>There is no items to remove</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="41"/>
        <source>当前配置文件的配置项目数为0，所以无法删除项目。</source>
        <translation>There is no items in the current configuration file, so cannot remove item.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="51"/>
        <source>（空行）</source>
        <translation>(Empty line)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="53"/>
        <source>（注释）</source>
        <translation>(Comments)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="55"/>
        <source>（元标记）</source>
        <translation>(Meta flags)</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="58"/>
        <source>指定元标记的序数</source>
        <translation>Specify the ordinal number meta flag uses</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="58"/>
        <source>在下面的输入框中输入一个数字。该数字将作为调用元标记时应当使用的序数。比如，您想要使用M1，就在下框中输入1.</source>
        <translation>Enter a number in the input box below.This number will be used as the ordinal number that should be used when calling the meta tag.For example, if you want to use M1, just enter &quot;1&quot; in the box below.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="78"/>
        <source>您设置的值“%1”无法应用于第%2行。请修改后重试。
</source>
        <translation>The value &quot;%1&quot; you set cannot be applied to line %2. Please modify and try again.
</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="81"/>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="90"/>
        <source>设置的值无效</source>
        <translation>Invalid value</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsdialog.cpp" line="90"/>
        <source>您设置的值“%1”无法应用于第%2行。请修改后重试。</source>
        <translation>The value &quot;%1&quot; you set cannot be applied to line %2. Please modify and try again.</translation>
    </message>
</context>
<context>
    <name>MoresamplerConfigsModel</name>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="16"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="32"/>
        <source>设置项</source>
        <translation>Configuration items</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="18"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="34"/>
        <source>值</source>
        <translation>Value</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="20"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="36"/>
        <source>分类</source>
        <translation>Type</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="22"/>
        <source>是否覆盖声库配置</source>
        <translation>Overwrite voicebank configuration</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="24"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="38"/>
        <source>说明</source>
        <translation>Note</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="73"/>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="123"/>
        <source>是</source>
        <translation>Yes</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="73"/>
        <source>否</source>
        <translation>No</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfigsmodel.cpp" line="75"/>
        <source>（不支持）</source>
        <translation>(Unsupported)</translation>
    </message>
</context>
<context>
    <name>MoresamplerHelp</name>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="222"/>
        <source>输出的 .wav 文件的采样频率</source>
        <translation>Sampling frequency of output .wav file</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="223"/>
        <source>输出的 .wav 文件的位深</source>
        <translation>Bit depth of output .wav file</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="224"/>
        <source>开启时, 在resampler模式下生成 .wav 文件 （用于与其他wavtool兼容）。此选项将减慢合成。</source>
        <translation>When turned on, generate .wav file in resampler mode (to be compatible with other wavtools); slows down synthesis。</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="225"/>
        <source>对每个音符应用自适应增益，使得当音量为100％时，合成波形的峰值达到最大幅度的一半。full: 对浊音和清音均进行增益； voiced: 只增益浊音；off: 不改变音量。</source>
        <translation>Apply an adaptive gain to each note such that the peak of synthesized waveform goes to half of the maximum amplitude when volume is 100%; full: gain both voiced and unvoiced parts; voiced: only gain voiced part; off: do not adjust volume. Example (full,voiced,off from top to bottom).</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="226"/>
        <source>基于心理声学响度测量，在修改后使可感知响度保持。</source>
        <translation>Retain the perceived loudness after modification, based on a psychoacoustic loudness measure. Example (off, on from top to bottom).</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="227"/>
        <source>决定Moresampler如何使音符时间变长。auto: 根据源时长和目标时长自动决定是使用拉伸方式还是循环方式。可使用 e 和 Me flag 来覆盖这一行为。</source>
        <translation>Determines how Moresampler extends the duration of each note; auto: automatically stretch or loop the note based on its original and target duration. The effect can be overwritten by e and Me flags.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="228"/>
        <source>on: wavtool模式下的合成将多线程运行（将会更快）。full: resampler模式也将在多线程运行。“多线程”意味着将多个线程包装于一个进程中，与同一时间运行多个Moresampler的“多进程”有着本质不同。注意，该特性不被 moresampler-legacy.exe支持。</source>
        <translation>When turned on, the final synthesis stage in wavtool mode will run in multiple threads (which means faster). When set to &quot;full&quot;, resampler mode will also become multithreaded. &quot;multithread&quot;, which packs multiple threads into a process, is inherently different from &quot;multiprocess&quot; which launches multiple instances of Moresampler at a time. Note: this feature is not supported by moresampler-legacy.exe.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="229"/>
        <source>检查.wav 文件与对应.llsm 文件和mrq数据项的最后修改时间。如果.wav文件比.llsm要新，则进行重分析。若.wav文件也比mrq数据项要新，则在重分析以生成.llsm文件前进行音高重估计。此特性或许对声库开发者有帮助。</source>
        <translation>Check the last modified time of .wav file and corresponding .llsm file and mrq data entry. If the .wav file is newer than the .llsm file, then reanalyze. If the .wav file is also newer than the mrq data entry, then reestimate pitch before reanalyzing .llsm. This feature might be helpful for voicebank developers.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="230"/>
        <source>在指定文件路径中输出Debug信息。</source>
        <translation>Output debug information into a specified file path.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="231"/>
        <source>从文件夹名推测音高。例如，如果给定的样本位于一个名为“C_D4”的文件夹下，Moresampler将在接近D4的范围（294 Hz左右）内进行音高分析。</source>
        <translation>Infer the pitch range from directory name. For example, if the given sample is under a directory named &quot;C_D4&quot;, Moresampler would run pitch analysis in a range close to D4 (around 294Hz).</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="232"/>
        <source>在接合音高与浊音行为估计期间增大浊音化概率，随后进行浊音音高修正；旨在提高特异度和降低灵敏度；适用于嘈杂/粗糙的语音，但会降低干净/流畅语音的质量。</source>
        <translation>(over)Emphasize voicing probability during joint pitch &amp; voicing activity estimation, followed by a pitch &amp; voicing correction procedure; tend to reduce false negative but raise false positive rate; works for noisy/coarse speech but degrades the quality of clean/smooth speech.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="233"/>
        <source>音高的下界(以Hz为单位)。</source>
        <translation>The lower bound for pitch (in Hz).</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="234"/>
        <source>音高的上界(以Hz为单位)。</source>
        <translation>The upper bound for pitch (in Hz).</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="235"/>
        <source>strict : 当desc.mrq不可用时，从.frq 文件读取音高数据。on : 使用 .frq 文件的音高数据来修正Moresampler自己对音高的猜测。不管该选项是否开启，结果都会保存至desc.mrq。注意：除非被仔细修正，.frq文件提供的音高数据通常无法足够可靠地使Moresampler运作。</source>
        <translation>When desc.mrq is not available, load pitch data from .frq file when set to strict; when set to on, use pitch data from .frq file to correct the pitch estimated by Moresampler&apos;s own estimator. No matter this option is turned on or not, the result will always be written into desc.mrq. Note: unless carefully corrected, pitch provided by .frq files are often not robust enough for Moresampler to run properly.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="236"/>
        <source>on : Moresampler将自动修复由噪声失真或低音量（量化误差）引起的分析错误。这些错误可能造成音高变换后的“尖锐”与“粗糙”的声音。然而此特性（理论上）可能导致轻微模糊。</source>
        <translation>When turned on, Moresampler will automatically fix analysis inaccuracy caused by noise distortion or low volume (quantization error) which may result in &quot;sharp&quot;, &quot;gross&quot; voice after pitch shifting. However turning on this feature may (in theory) slightly blur the speech. Example (off, on from top to bottom).</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="237"/>
        <source>在从.wav文件分析LLSM时自动降噪。更适用于长录音。</source>
        <translation>Automatically reduces noise when analyzing LLSM from .wav; works better with longer recordings.</translation>
    </message>
    <message>
        <location filename="EngineUtils/moresamplerconfig.cpp" line="238"/>
        <source>在分析时自动移除输入中存在的次谐波。对尖亮的声音可能有帮助，但会导致呼吸音的质量降低。</source>
        <translation>Automatically remove the subharmonics (if there&apos;s any) from input speech during analysis. Might be helpful for screamy voices but slightly degrades the quality of breathy voices.</translation>
    </message>
</context>
<context>
    <name>TextCodecConvertDialog</name>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="14"/>
        <source>转换文本编码</source>
        <translation>Convert text encoding</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="20"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="61"/>
        <source>支持的编码</source>
        <translation>Supported encodings</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="31"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="95"/>
        <source>Shift-JIS</source>
        <translation></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="36"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="100"/>
        <source>GB18030</source>
        <translation></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="41"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="105"/>
        <source>Big5</source>
        <translation></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="46"/>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="110"/>
        <source>UTF-8</source>
        <translation></translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="54"/>
        <source>转换后文本预览：</source>
        <translation>Converted text preview:</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="81"/>
        <source>转换前文本：</source>
        <translation>Original text:</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="118"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;打开此项后，程序将在预览窗口中同时输出系统编码下对您选择编码字符串的重解码后的显示效果。对文件名转换来说，此项十分有帮助。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;When this item is turned on, the program will simultaneously output the re-decoded display effect of the selected encoding string under the system encoding in the preview window.This is very helpful for file name conversion.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.ui" line="121"/>
        <source>在预览中输出在系统编码下重解码的预览</source>
        <translation>Output preview of re-decoding under system encoding in preview</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.cpp" line="97"/>
        <source>&lt;h4&gt;以%1进行解码的预览：&lt;/h4&gt;&lt;pre&gt;%2&lt;/pre&gt;&lt;h4&gt;使用系统编码重解码后的预览&lt;/h4&gt;&lt;pre&gt;%3&lt;/pre&gt;</source>
        <translation>&lt;h4&gt;Preview decoding in %1:&lt;/h4&gt;&lt;pre&gt;%2&lt;/pre&gt;&lt;h4&gt;Preview re-decoding under system encoding:&lt;/h4&gt;&lt;pre&gt;%3&lt;/pre&gt;</translation>
    </message>
    <message>
        <location filename="TextCodecUtils/textcodecconvertdialog.cpp" line="129"/>
        <source>对%1进行编码转换</source>
        <translation>Convert encoding of %1</translation>
    </message>
</context>
<context>
    <name>TextCodecSettingDialog</name>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="14"/>
        <source>文本编码设定</source>
        <translation>Text encoding setting</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="52"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="83"/>
        <source>readme.txt的字符编码</source>
        <translation>Text encoding of readme.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="29"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="70"/>
        <source>Shift-JIS</source>
        <translation></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="34"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="75"/>
        <source>GB18030</source>
        <translation></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="39"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="80"/>
        <source>Big5</source>
        <translation></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="44"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="85"/>
        <source>UTF-8</source>
        <translation></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="107"/>
        <source>跟随默认编码？</source>
        <translation>Follow default encoding?</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="59"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="82"/>
        <source>character.txt的字符编码</source>
        <translation>Text encoding of character.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="93"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="100"/>
        <source>支持的编码</source>
        <translation>Supported encodings</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="114"/>
        <source>自动探测？（仅对文本文件生效）</source>
        <translation>Auto detect? (Only for text files)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="123"/>
        <source>要设置文本编码的音源：</source>
        <translation>Voicebank to set text encoding:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="130"/>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="101"/>
        <source>（默认编码）</source>
        <translation>(Default encoding)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.ui" line="137"/>
        <source>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;注意：如果您要手动指定编码的话，请注意输入QTextCodec的codecForName()函数支持的编码对应字符串。&lt;/p&gt;&lt;p&gt;您可以使用文本框旁的按钮来查看QTextCodec支持的编码及其别名，双击或选择后确定可以直接应用至本对话框。&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</source>
        <translation>&lt;html&gt;&lt;head/&gt;&lt;body&gt;&lt;p&gt;Note: If you want to specify the encoding manually, please type the encoding corresponding string supported by QTextCodec&apos;s codecForName() function.&lt;/p&gt;&lt;p&gt;You can use the button next to the text box to view the encodings supported by QTextCodec and their aliases. Double-click or select to apply directly to this dialog.&lt;/p&gt;&lt;/body&gt;&lt;/html&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="62"/>
        <source>（备选）character.txt的字符编码</source>
        <translation>(Alternative) Text encoding of character.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="63"/>
        <source>（备选）readme.txt的字符编码</source>
        <translation>(Alternative) Text encoding of readme.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/textcodecsettingdialog.cpp" line="89"/>
        <source>设定%1的读取用文本编码</source>
        <translation>Set reading text encoding for %1</translation>
    </message>
</context>
<context>
    <name>VoiceBank</name>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="836"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：没有为此音源库找到character.txt。在音源使用过程中将无法查看音源名称、图像等信息。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: No character.txt was found for this voicebank. You will not be able to view the name, image, etc. during the use of the voicebank.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="850"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中的name字段没有被设定。在音源使用过程中音源区域将显示文件夹名称。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: The name field in character.txt is not set. The folder name will be displayed in the voicebank information area.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="864"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中的image字段没有被设定。在音源使用过程中音源区域将不显示图片。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: The image field in character.txt is not set. The voicebank icon will not be displayed in the voicebank information area.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="878"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。&lt;/p&gt;</source>
        <oldsource>(&lt;p style=&quot;color:red&quot;&gt;错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。&lt;/p&gt;</oldsource>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error：Can&apos;t found the image file setting in character.txt(%1). The voicebank icon will not be displayed in the voicebank information area.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="893"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中设定的图片文件没有正常读取。是不是图片格式与后缀名不符？亦或是文件损坏？&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: The image file setting in character.txt is not read properly. Is the image format not matching the suffix name? Or is the file damaged?&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="895"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：character.txt中设定的图片文件（%1*%2）不符合UTAU的图标要求（比例1:1）。在音源使用过程中将音源区域图片可能显示不正确，或者无法显示。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: The image file (%1*%2) setting in character.txt does not meet the UTAU icon requirements (ratio 1:1). The voicebank icon may not be displayed correctly during the use of the voicebank or may not be displayed.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="909"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：找不到readme.txt。音源的README将无法显示。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: readme.txt could not be found. The README of the voicebank will not be displayed.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="923"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：在读取音源图片时发生了一个异常。或许重载此音源能解决这个问题。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: An exception occurred while reading the source image. Perhaps reloading this voicebank can solve this problem. &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="937"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：无法打开readme.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: Unable to open readme.txt. Perhaps occupied by other programs? Or is it a file system issue? The log can provide more information. &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="951"/>
        <source>&lt;p style=&quot;color:red&quot;&gt;错误：无法打开character.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:red&quot;&gt;Error: Unable to open character.txt. Perhaps occupied by other programs? Or is it a file system issue? The log can provide more information. &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="965"/>
        <source>&lt;p style=&quot;color:orange&quot;&gt;警告：无法探测character.txt的编码。程序将使用默认编码。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:orange&quot;&gt;Warning: The encoding of character.txt could not be detected. The program will use the default encoding. &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebank.cpp" line="979"/>
        <source>&lt;p style=&quot;color:orange&quot;&gt;警告：无法探测readme.txt的编码。程序将使用默认编码。&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:orange&quot;&gt;Warning: The encoding of readme.txt could not be detected. The program will use the default encoding. &lt;/p&gt;</translation>
    </message>
</context>
<context>
    <name>VoiceBankHandler</name>
    <message>
        <location filename="VoiceBankUtils/voicebankhandler.cpp" line="96"/>
        <source>未分类</source>
        <translation>Uncategorized</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankhandler.cpp" line="124"/>
        <source>无标签</source>
        <translation>No labels</translation>
    </message>
</context>
<context>
    <name>VoiceBankIconCropDialog</name>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.ui" line="23"/>
        <source>键入目标文件名，文件格式将根据后缀自动推断。透明度将会在白色背景上绘制后再保存。默认为“icon.jpg”</source>
        <translation>Type the target file name, whose format will be automatically inferred based on the suffix. Transparency will be drawn on a white background before saving. The default is &quot;icon.jpg&quot;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.ui" line="30"/>
        <source>目标文件名：</source>
        <translation>Target file name:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.ui" line="47"/>
        <source>在选择好作为图标的范围之后，按下确定以应用</source>
        <translation>After selecting the range to crop as the icon, press OK to apply</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankiconcropdialog.cpp" line="11"/>
        <source>为音源库“%1”设定新图标</source>
        <translation>Set a new icon for the voicebank &quot;%1&quot;</translation>
    </message>
</context>
<context>
    <name>VoiceBankManagerWindow</name>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="14"/>
        <source>音源管理器</source>
        <translation>Voicebank Manager</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="46"/>
        <source>音源库列表：</source>
        <translation>Voicebank list:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="63"/>
        <source>键入以搜索</source>
        <translation>Type to search</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="266"/>
        <source>文件</source>
        <translation>File</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="274"/>
        <source>选项</source>
        <translation>Options</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="278"/>
        <source>语言（Language）</source>
        <translation>Language</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="291"/>
        <source>帮助</source>
        <translation>Help</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="298"/>
        <source>工具</source>
        <translation>Tools</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="302"/>
        <source>（独立）编码转换器</source>
        <translation>(Independent) Encoding Converter</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="181"/>
        <source>播放样例</source>
        <translation>Play sample</translation>
    </message>
    <message>
        <source>音源库名称</source>
        <translation type="vanished">Voicebank Name</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="319"/>
        <source>导入音源库...</source>
        <translation>Import voicebanks...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="322"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="325"/>
        <source>导入一个外部音源库用于管理</source>
        <translation>Import an outside voicebank to manage</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="330"/>
        <source>重载</source>
        <translation>Reload</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="333"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="336"/>
        <source>重新载入监视文件夹下的音源库</source>
        <translation>Reload the voicebanks under the watched folder</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="341"/>
        <source>对选定的音源库进行原音设定（oto.ini）...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="344"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="347"/>
        <source>在原音设定编辑器中编辑该音源库的oto.ini</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="352"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="355"/>
        <source>退出</source>
        <translation>Exit</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="360"/>
        <source>监视文件夹...</source>
        <translation>Watched Folder...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="363"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="366"/>
        <source>修改程序寻找音源的位置</source>
        <translation>Modify the location to find the voicebank</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="371"/>
        <source>默认文本编码...</source>
        <translation>Default text encoding...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="374"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="377"/>
        <source>修改程序读取音源文件时默认使用的编码</source>
        <translation>Modify the text encoding used by the program when reading the voicebank&apos;s file by default</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="382"/>
        <source>关于</source>
        <translation>About</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="385"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="388"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="882"/>
        <source>关于本程序</source>
        <translation>About this program</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="396"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="898"/>
        <source>关于 Qt</source>
        <translation>About Qt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="399"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="402"/>
        <source>关于本程序使用的 Qt 框架</source>
        <translation>About the Qt Framework this program uses</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="410"/>
        <source>设置读取用线程池的最大大小...</source>
        <translation>Set the maximum size of the thread pool for reading...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="413"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="416"/>
        <source>（高级）改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。</source>
        <translation>(Advanced) Change the maximum number of threads when the program reads the voicebank. Make sure you change this setting after you know what you are doing.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="421"/>
        <source>编辑全局Moresampler设置</source>
        <translation>Edit global Moresampler configuration</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="424"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="427"/>
        <source>在编辑器中打开一个moreconfig.txt并以全局模式编辑</source>
        <translation>Open a moreconfig.txt in the editor and edit it in global mode</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="432"/>
        <source>随机选择一个音源</source>
        <translation>Choose a voicebank randomly</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="435"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="438"/>
        <source>在音源列表中随机选择一个音源。在拿不定主意的时候说不定会有帮助。</source>
        <translation>Randomly select a voicebank in the list. Maybe it will help when you have no idea.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="443"/>
        <source>转换文本文件...</source>
        <translation>Convert text file...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="446"/>
        <source>在文件编码转换器中打开一个文本文件</source>
        <translation>Open a text file in the file encoding converter</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="451"/>
        <source>转换文件名...</source>
        <translation>Convert file names...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="454"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="457"/>
        <source>在文件编码转换器中打开一个文件夹以转换文件名。程序只会转换当前文件夹下的文件和文件夹名。</source>
        <oldsource>在文件编码转换器中打开一个文件夹以转换文件名。程序只会转换一级文件和文件夹的名称。</oldsource>
        <translation>Open a folder in the text encoding converter to convert the file names in the folder. The program will only convert the file and folder names under the given folder.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="468"/>
        <source>自动推断（Auto detect）</source>
        <translation>Auto detect</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="471"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="474"/>
        <source>让程序自行确认所需使用的语言文件</source>
        <translation>Let program decide what translation file should use</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="482"/>
        <source>不翻译（简体中文）（Don&apos;t translate(Simplified Chinese)）</source>
        <translation>Don&apos;t translate (Simplified Chinese)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="485"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="488"/>
        <source>不使用翻译文件。程序将显示为简体中文。</source>
        <translation>Don&apos;t use translation file. Program will show in Simplified Chinese.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="496"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="99"/>
        <source>载入一个翻译文件（Load a translation file...）</source>
        <translation>Load a translation file...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="499"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.ui" line="502"/>
        <source>浏览一个外部翻译文件并载入程序。</source>
        <translation>Open a external translation file and use it.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="116"/>
        <source>无法加载语言文件%1。等同于自动推断。(Can&apos;t load language file %1. Equal to auto-detect.)</source>
        <translation>Can&apos;t load language file %1. Equal to auto-detect.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="125"/>
        <source>没有指定语言文件。等同于自动推断。(No language file is selected. Equal to auto-detect.)</source>
        <translation>No language file is selected. Equal to auto-detect.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="171"/>
        <source>加载中</source>
        <translation>Loading</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="277"/>
        <source>&lt;p style=&quot;color:blue&quot;&gt;自动探测后程序使用的文本编码：character.txt：%1。readme.txt：%2&lt;/p&gt;</source>
        <translation>&lt;p style=&quot;color:blue&quot;&gt;Text encoding used by the program after automatic detection: character.txt: %1. readme.txt: %2&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="297"/>
        <source>共 %1 个</source>
        <translation>%1 in total</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="300"/>
        <source>没有音源。</source>
        <translation>No voicebanks.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="313"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="315"/>
        <source>音源“%1”读取完毕</source>
        <translation>Voicebank &quot;%1&quot; read done</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="334"/>
        <source>打开...</source>
        <translation>Open...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="336"/>
        <source>打开音源文件夹</source>
        <translation>Open the folder of the voicebank</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="338"/>
        <source>在资源管理器中打开该音源的文件夹。</source>
        <translation>Open the folder of the voicebank in explorer.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="341"/>
        <source>打开character.txt</source>
        <translation>Open character.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="343"/>
        <source>在系统关联的文本编辑器中打开该音源的character.txt。</source>
        <translation>Open the character.txt of the voicebank in the text editor associated with the system.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="346"/>
        <source>打开readme.txt</source>
        <translation>Open readme.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="348"/>
        <source>在系统关联的文本编辑器中打开该音源的readme.txt。</source>
        <translation>Open the readme.txt of the voicebank in the text editor associated with the system.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="353"/>
        <source>复制...路径</source>
        <translation>Copy the path of ...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="355"/>
        <source>复制音源路径</source>
        <translation>Copy the path of the voicebank</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="357"/>
        <source>复制该音源的文件夹路径到剪贴板。</source>
        <translation>Copy the folder path of the voicebank to the clipboard.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="360"/>
        <source>复制character.txt的文件路径</source>
        <translation>Copy the path of the character.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="362"/>
        <source>复制该音源的character.txt的路径到剪贴板。</source>
        <translation>Copy the folder path of the character.txt to the clipboard.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="365"/>
        <source>复制readme.txt的文件路径</source>
        <translation>Copy the path of the readme.txt</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="367"/>
        <source>复制该音源的readme.txt路径到剪贴板。</source>
        <translation>Copy the folder path of the readme.txt to the clipboard.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="372"/>
        <source>修改...</source>
        <translation>Modify...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="374"/>
        <source>修改音源的名称...</source>
        <translation>Modify the name of the voicebank...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="376"/>
        <source>为该音源指定一个新名称。</source>
        <translation>Give the voicebank a new name.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="379"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1188"/>
        <source>修改音源的图标...</source>
        <translation>Modify the icon of the voicebank...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="381"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1190"/>
        <source>为该音源指定一个新图标。</source>
        <translation>Assign a new icon to the voicebank.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="387"/>
        <source>编码相关</source>
        <translation>Encoding related</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="389"/>
        <source>为该音源单独设置文本编码...</source>
        <translation>Set the text encoding separately for the voicebank...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="391"/>
        <source>为该音源设置读取用文本编码。注意，这仅在本软件中有效。</source>
        <translation>Set the text encoding for reading for this voicebank. Note that this is only valid in this program.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="396"/>
        <source>对character.txt进行编码转换...</source>
        <translation>Convert text encoding of character.txt...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="398"/>
        <source>在文件编码转换器中转换该音源character.txt的编码。</source>
        <translation>Open the character.txt in the file encoding converter.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="401"/>
        <source>对readme.txt进行编码转换...</source>
        <translation>Convert text encoding of readme.txt...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="403"/>
        <source>在文件编码转换器中转换该音源readme.txt的编码。</source>
        <translation>Open the readme.txt in the file encoding converter.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="406"/>
        <source>对WAV文件名进行编码转换...</source>
        <translation>Convert text encoding of the WAV file names...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="408"/>
        <source>在文件编码转换器中转换该音源的WAV文件名的编码。</source>
        <translation>Convert the WAV file names in the text encoding converter.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="413"/>
        <source>引擎相关</source>
        <translation>Engine related</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="415"/>
        <source>编辑该音源的Moresampler声库配置...</source>
        <translation>Edit Moresampler configurations of the voicebank...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="417"/>
        <source>编辑该声库的Moresampler声库配置。只有在您使用Moresampler时起效。</source>
        <translation>Edit the Moresampler configuration for this voicebank. Only works when you use Moresampler.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="430"/>
        <source>重载此音源</source>
        <translation>Reload the voicebank</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="432"/>
        <source>重新从硬盘加载此音源。</source>
        <translation>reload the voicebank from disk.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="441"/>
        <source>新建一个分类...</source>
        <translation>Create a new category...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="446"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="505"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="919"/>
        <source>未分类</source>
        <translation>Uncategorized</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="463"/>
        <source>新建一个标签...</source>
        <translation>Create a new label...</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="480"/>
        <source>输入新标签的名称</source>
        <translation>Enter the name of the new label</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="480"/>
        <source>输入新标签的名称：</source>
        <translation>Enter the name of the new label:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="512"/>
        <source>输入新分类的名称</source>
        <translation>Enter the name of the new category</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="512"/>
        <source>输入新分类的名称：</source>
        <translation>Enter the name of the new category:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="560"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="580"/>
        <source>打开失败</source>
        <translation>Fail to open</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="560"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="580"/>
        <source>无法打开%1。</source>
        <translation>Can&apos;t open %1.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="602"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="620"/>
        <source>剪贴板仍会被更改</source>
        <translation>The clipboard will still be changed</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="602"/>
        <source>即使您没有要求程序创建character.txt，程序也将把路径复制到剪贴板。但还是请您注意，这个路径并没有指向有效的文件。</source>
        <translation>Even if you don&apos;t ask the program to create character.txt, the program will copy the path to the clipboard. But please note that this path does not point to a valid file.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="620"/>
        <source>即使您没有要求程序创建readme.txt，程序也将把路径复制到剪贴板。但还是请您注意，这个路径并没有指向有效的文件。</source>
        <translation>Even if you don&apos;t ask the program to create readme.txt, the program will copy the path to the clipboard. But please note that this path does not point to a valid file.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="646"/>
        <source>character.txt不存在</source>
        <translation>The character.txt does not exist</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="646"/>
        <source>您选定的音源不存在character.txt。所以无法进行转换操作。</source>
        <translation>The character.txt does not exist for the voicebank you selected. Therefore, the conversion operation cannot be performed.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="665"/>
        <source>readme.txt不存在</source>
        <translation>The readme.txt does not exist</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="665"/>
        <source>您选定的音源不存在readme.txt。所以无法进行转换操作。</source>
        <translation>The readme.txt does not exist for the voicebank you selected. Therefore, the conversion operation cannot be performed.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="732"/>
        <source>%1的WAV文件名</source>
        <translation>The WAV file names of %1</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="801"/>
        <source>监视文件夹列表被更改</source>
        <translation>Watched folders list is modified</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="801"/>
        <source>您更改了监视文件夹列表，是否立即重载音源库列表？</source>
        <translation>You&apos;ve changed the watched folders list, Do you want to reload the list of voicebanks immediately?</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="821"/>
        <source>默认文本读取编码被更改</source>
        <translation>Default text encoding for reading is modified</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="821"/>
        <source>您更改了默认的读取用文本编码，是否立即重载音源库列表？</source>
        <translation>You&apos;ve changed the defalut text encoding for reading, Do you want to reload the list of voicebanks immediately?</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="882"/>
        <source>&lt;h3&gt;音源管理器&lt;/h3&gt;&lt;p&gt;版本：%1 作者：shine_5402&lt;/p&gt;&lt;p&gt;本程序以 Apache License Version 2.0 分发。&lt;/p&gt;&lt;p&gt;“音源管理器”是为UTAU程序所用音源设计的本地信息管理器。&lt;/p&gt;&lt;p&gt;本程序是 &lt;a href=&quot;https://github.com/shine5402/LeafOpenUTAUQt&quot;&gt;Leaf OpenUTAU Qt Project&lt;/a&gt; 的一部分&lt;/p&gt;&lt;p&gt;UTAU是一款由饴屋/菖蒲（あめや・あやめ）氏开发的免费的歌声合成软件。&lt;/p&gt;&lt;p&gt;本程序使用了以下开源项目：&lt;/p&gt;&lt;ul&gt;&lt;li&gt;LeafPublicQtClasses by shine_5402 (Apache License Version 2.0)&lt;/li&gt;&lt;li&gt;ImageCropper by dimkanovikov and shine_5402 (GNU LGPL v3)&lt;/li&gt;&lt;li&gt;libchardet by JoungKyun.Kim (MPL 1.1 or LGPL 2.1)&lt;/li&gt;&lt;/ul&gt;</source>
        <translation>&lt;h3&gt;Voicebank Manager&lt;/h3&gt;&lt;p&gt;Version: %1 Author: shine_5402&lt;/p&gt;&lt;p&gt;The program is licensed under Apache License Version 2.0.&lt;/p&gt;&lt;p&gt;&quot;Voicebank Manager&quot; is a information manager designed for the voicebanks for UTAU program.&lt;/p&gt;&lt;p&gt;The program is a part of &lt;a href=&quot;https://github.com/shine5402/LeafOpenUTAUQt&quot;&gt;Leaf OpenUTAU Qt Project&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;UTAU is a Japanese singing synthesizer application created by Ameya/Ayame.&lt;/p&gt;&lt;p&gt;The program uses following opensourse projects:&lt;/p&gt;&lt;ul&gt;&lt;li&gt;LeafPublicQtClasses by shine_5402 (Apache License Version 2.0)&lt;/li&gt;&lt;li&gt;ImageCropper by dimkanovikov and shine_5402 (GNU LGPL v3)&lt;/li&gt;&lt;li&gt;libchardet by JoungKyun.Kim (MPL 1.1 or LGPL 2.1)&lt;/li&gt;&lt;/ul&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1155"/>
        <source>打开一个文本文件</source>
        <translation>Open a text file</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1163"/>
        <source>打开一个文件夹</source>
        <translation>Open a folder</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1181"/>
        <source>转换%1下的文件名</source>
        <translation>Convert file name encoding in %1</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1182"/>
        <source>对%1下的文件名的转换成功完成。</source>
        <translation>The encoding conversion of the file name under %1 was completed successfully.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="703"/>
        <source>%1（%2）</source>
        <translation>%1 (%2)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="712"/>
        <source>转换中出了些问题</source>
        <translation>Some problems in the conversion</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="712"/>
        <source>&lt;h3&gt;程序在转换以下文件时出了些错误&lt;/h3&gt;&lt;pre&gt;%1&lt;/pre&gt;&lt;p&gt;这些文件应当都保持在原有的状态。您可以排查问题后重试。&lt;/p&gt;</source>
        <translation>&lt;h3&gt;The program meet some errors while converting the following files.&lt;/h3&gt;&lt;pre&gt;%1&lt;/pre&gt;&lt;p&gt;These files should all remain in their original state. You can try after troubleshooting.&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="736"/>
        <source>转换成功完成</source>
        <translation>Conversion completed successfully</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="736"/>
        <source>音源%1的WAV文件名均已从%2转换至%3。</source>
        <translation>The WAV file name of voicebank %1 has been converted from %2 to %3.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="745"/>
        <source>文件不存在</source>
        <translation>The file doesn&apos;t exist</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="745"/>
        <source>文件%1不存在</source>
        <translation>The file %1 doesn&apos;t exist</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="754"/>
        <source>即将执行编码转换</source>
        <translation>Encoding conversion is about to be performed</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="754"/>
        <source>&lt;h3&gt;程序即将对%1执行编码转换（%2 -&gt; %3）&lt;/h3&gt;&lt;p&gt;在您单击确定后，程序将会把转换后的结果保存至%1。&lt;/p&gt;&lt;p&gt;但是，程序有必要提醒您编码转换的&lt;b&gt;风险&lt;/b&gt;：由于源编码和目标编码间的可能的映射不对等关系，这种转换可能&lt;b&gt;不可逆&lt;/b&gt;，并且可能使您&lt;b&gt;丢失数据&lt;/b&gt;！&lt;/p&gt;&lt;p&gt;出于安全考虑，程序将保存一份源文件的备份副本（%1.bak），以便出现问题时您可以手动恢复。&lt;/p&gt;&lt;p&gt;确定要执行转换吗？&lt;/p&gt;</source>
        <translation>&lt;h3&gt;The program will perform code conversion on %1 (%2 -&gt; %3)&lt;/h3&gt;&lt;p&gt; After you click OK, the program will save the converted result to %1. &lt;/p&gt;&lt;p&gt;However, it is necessary for the program to remind you of the &lt;b&gt;risk&lt;/b&gt; of the encoding conversion: due to the possible not equal mapping between the source encoding and the target encoding, the conversion may be &lt;b&gt;irreversible&lt; /b&gt;, and may make you &lt;b&gt;lose data&lt;/b&gt;! &lt;/p&gt;&lt;p&gt;For security reasons, the program will save a backup copy of the source file (%1.bak) so that you can manually recover it if something goes wrong. &lt;/p&gt;&lt;p&gt;Are you sure you want to perform the conversion? &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="763"/>
        <source>转换失败</source>
        <translation>Fail to convert</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="763"/>
        <source>&lt;h3&gt;程序无法对%1进行写入&lt;/h3&gt;&lt;p&gt;在写入时出现错误。Qt提供的错误描述为%2。&lt;/p&gt;&lt;p&gt;文件应该没有被修改。&lt;/p&gt;</source>
        <translation>&lt;h3&gt;The program could not write to %1&lt;/h3&gt;&lt;p&gt;An error occurred while writing. The error description provided by Qt is %2. &lt;/p&gt;&lt;p&gt;The file should not have been modified. &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="767"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1182"/>
        <source>转换成功</source>
        <translation>Conversion completed successfully</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="767"/>
        <source>&lt;h3&gt;文件编码转换完成&lt;/h3&gt;&lt;p&gt;程序将自动修改该文件的读取用文本编码，之后将实施重载。&lt;/p&gt;</source>
        <translation>&lt;h3&gt;File encoding conversion completed&lt;/h3&gt;&lt;p&gt;The program will automatically modify the text encoding for reading the file, and then reload the voicebank. &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="775"/>
        <source>无法备份%1</source>
        <translation>Can&apos;t backup %1</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="775"/>
        <source>&lt;h3&gt;程序无法对%1进行备份&lt;/h3&gt;&lt;p&gt;在备份时出现错误。Qt提供的错误说明为：%2&lt;/p&gt;&lt;p&gt;你仍可以令程序继续转换，但是之前提到的&lt;b&gt;风险&lt;/b&gt;仍然存在，且出现问题时您无法恢复。&lt;/p&gt;&lt;p&gt;确定要继续转换吗？&lt;/p&gt;</source>
        <translation>&lt;h3&gt;The program could not backup %1&lt;/h3&gt;&lt;p&gt;An error occurred during backup. The error description provided by Qt is: %2&lt;/p&gt;&lt;p&gt;You can still make the program continue to convert, but the previously mentioned &lt;b&gt;risk&lt;/b&gt; still exists and you cannot recover when error occurs. &lt;/p&gt;&lt;p&gt;Are you sure you want to continue the conversion? &lt;/p&gt;</translation>
    </message>
    <message>
        <source>&lt;h3&gt;音源管理器&lt;/h3&gt;&lt;p&gt;版本：%1 作者：shine_5402&lt;/p&gt;&lt;p&gt;本程序以 Apache License Version 2.0 分发。&lt;/p&gt;&lt;p&gt;“音源管理器”是为UTAU程序所用音源设计的本地信息管理器。&lt;/p&gt;&lt;p&gt;本程序是 &lt;a href=&quot;https://github.com/shine5402/LeafOpenUTAUQt&quot;&gt;Leaf OpenUTAU Qt Project&lt;/a&gt; 的一部分&lt;/p&gt;&lt;p&gt;UTAU是一款由饴屋/菖蒲（あめや・あやめ）氏开发的免费的歌声合成软件。&lt;/p&gt;&lt;p&gt;本程序使用了以下开源项目：&lt;/p&gt;&lt;ul&gt;&lt;li&gt;LeafPublicQtClasses by shine_5402 (Apache License Version 2.0)&lt;/li&gt;&lt;li&gt;ImageCropper by dimkanovikov and shine_5402 (GNU LGPL v3)&lt;/li&gt;&lt;/ul&gt;</source>
        <translation type="vanished">&lt;h3&gt;Voicebank Manager&lt;/h3&gt;&lt;p&gt;Versioon: %1 Author: shine_5402&lt;/p&gt;&lt;p&gt;The program is licensed under Apache License Version 2.0.&lt;/p&gt;&lt;p&gt;&quot;Voicebank Manager&quot; is a information manager designed for the voicebanks for UTAU program.&lt;/p&gt;&lt;p&gt;The program is a part of &lt;a href=&quot;https://github.com/shine5402/LeafOpenUTAUQt&quot;&gt;Leaf OpenUTAU Qt Project&lt;/a&gt;.&lt;/p&gt;&lt;p&gt;UTAU is a Japanese singing synthesizer application created by Ameya/Ayame.&lt;/p&gt;&lt;p&gt;The program uses following opensourse projects:&lt;/p&gt;&lt;ul&gt;&lt;li&gt;LeafPublicQtClasses by shine_5402 (Apache License Version 2.0)&lt;/li&gt;&lt;li&gt;ImageCropper by dimkanovikov and shine_5402 (GNU LGPL v3)&lt;/li&gt;&lt;/ul&gt;</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="904"/>
        <source>设定线程池的最大大小</source>
        <translation>Set the maximum size of the thread pool</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="904"/>
        <source>（高级）该设置改变程序读取音源库时的最大线程数。请确保您在知道自己在做什么之后再更改此项设置。</source>
        <translation>(Advanced) This setting changes the maximum number of threads when the program reads the voicebank. Make sure you change this setting after you know what you are doing.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="907"/>
        <source>线程池大小已经被设置为%1</source>
        <translation>The thread pool size has been set to %1</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="955"/>
        <source>选择一个子文件夹</source>
        <translation>Select a subfolder</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="955"/>
        <source>您选择的音源有子文件夹。Moresampler的配置文件只对一个同文件夹内的wav文件起效。请选择一个子文件夹来编辑配置：</source>
        <translation>The voicebank you selected has subfolders. Moresampler&apos;s configuration file only works for the wav files in the same folder. Please select a subfolder to edit the configuration:</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="979"/>
        <source>检测到可能的全局配置</source>
        <translation>Possible global configuration files was detected</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="979"/>
        <source>在监视文件夹的父文件夹中发现了以下可能的Moresampler配置文件。您可以选择其中的一个打开，或者取消来进行浏览。</source>
        <translation>The following possible Moresampler configuration files were found in the parent folders of the watched folders. You can choose one of them to open, or cancel to browse.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="989"/>
        <source>打开一个Moresampler全局配置文件</source>
        <translation>Edit a global Moresampler configuration file</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="990"/>
        <source>Moresampler 配置文件 (moreconfig.txt)</source>
        <translation>Moresampler configuration file (moreconfig.txt)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1006"/>
        <source>为音源指定一个新名称</source>
        <translation>Give the voicebank a new name</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1006"/>
        <source>为路径为%1的音源指定一个新名称（程序会自动转换编码）：</source>
        <translation>Give the voicebank %1 a new name (program will convert text encoding automatically):</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1010"/>
        <source>已将路径为%1的音源的名称设置为%2。</source>
        <translation>The name of voicebank in &quot;%1&quot; has been set to %2.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1013"/>
        <source>文件无法被打开</source>
        <translation>The file can&apos;t be opened</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1013"/>
        <source>有一个文件无法被打开。Qt提供的错误字符串为%1</source>
        <translation>There is a file that cannot be opened. The error string provided by Qt is %1</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1017"/>
        <source>路径为%1的音源的character.txt不存在。程序已经自动创建并将名称设置为%1。</source>
        <translation>The character.txt of the voicebank whose path is %1 does not exist. The program has automatically created it and the name of voicebank is set to %1.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1034"/>
        <source>图像文件 (%1)</source>
        <translation>Image File (%1)</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1035"/>
        <source>选择要设定为图标的新图片</source>
        <translation>Select a new image to set as an icon</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1052"/>
        <source>没有音源</source>
        <translation>No voicebanks</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1052"/>
        <source>没有音源，无法随机选择音源。</source>
        <translation>There are no voicebanks here, so can&apos;t select a voicebank randomly.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1067"/>
        <source>备份了%1原先的图标，因为目标文件名已存在。</source>
        <translation>The previous icon of %1 was backed up because the target file name already exists.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1072"/>
        <source>无法备份</source>
        <translation>Can&apos;t backup</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1072"/>
        <source>因为重名，程序尝试备份%1原先的图标，但是遇到错误无法完成，操作终止。</source>
        <translation>The program tried to backup the previous icon of %1, but the operation was terminated because of the duplicate name.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1088"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1109"/>
        <source>没有可供播放的样例</source>
        <translation>There are no sample to play</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1088"/>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1109"/>
        <source>程序无法找到可供播放的样例文件。</source>
        <translation>The program could not find a sample file to play.</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.cpp" line="1123"/>
        <source>正在播放%1的声音样例</source>
        <translation>Playing the sample of %1</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.h" line="81"/>
        <source>分类</source>
        <translation>Categories</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankmanagerwindow.h" line="83"/>
        <source>标签</source>
        <translation>Labels</translation>
    </message>
</context>
<context>
    <name>VoiceBankReadmeInformationDialog</name>
    <message>
        <location filename="VoiceBankUtils/voicebankreadmeinformationdialog.ui" line="14"/>
        <source>音源库信息</source>
        <translation>Voicebank Infomarion</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankreadmeinformationdialog.ui" line="54"/>
        <source>播放样例</source>
        <translation>Play Sample</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebankreadmeinformationdialog.ui" line="80"/>
        <source>音源库名称</source>
        <translation>Voicebank Name</translation>
    </message>
</context>
<context>
    <name>VoiceBankTableModel</name>
    <message>
        <location filename="VoiceBankUtils/voicebanktablemodel.cpp" line="83"/>
        <source>音源名称</source>
        <translation>Name</translation>
    </message>
    <message>
        <location filename="VoiceBankUtils/voicebanktablemodel.cpp" line="85"/>
        <source>音源路径</source>
        <translation>Path</translation>
    </message>
</context>
</TS>
