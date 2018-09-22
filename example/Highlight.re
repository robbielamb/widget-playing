[@bs.module "react-fast-highlight"]
external highlightClass: ReasonReact.reactClass = "default";

type languageHighlightRules;
type highlighter;

[@bs.module] external highlightJs_ : highlighter = "highlight.js/lib/highlight";

[@bs.send] external registerLanguage : (highlighter, string, languageHighlightRules) => unit = ""; 
[@bs.module "reason-highlightjs"] external reasonHighlightJs : languageHighlightRules = "default";

let highlightJs = highlightJs_;


registerLanguage(highlightJs, "reason", reasonHighlightJs);

[@bs.deriving abstract]
type jsProps = {
  className: Js.nullable(string),
  languages: Js.nullable(array(string)),
  highlightjs: Js.nullable(highlighter),
};

let make =
    (
      ~className=?,
      ~languages=?,
      ~highlightjs=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=highlightClass,
    ~props=jsProps(
      ~className=Js.Nullable.fromOption(className),
      ~languages=Js.Nullable.fromOption(languages),
      ~highlightjs=Js.Nullable.fromOption(highlightjs),
    ),
    children,
  );
