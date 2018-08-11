include Utils;

let component = ReasonReact.statelessComponent("Jumbotron");

let make =
    (
      ~fluid: bool=false,
      ~tag: string="div",
      ~className: option(string)=?,
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children,
    ) => {
  ...component,
  render: _self => {
    let classes =
      ["jumbotron", fluid ? "jumbotron-fluid" : "", unwrapStr(i, className)]
      |> String.concat(" ");
    ReasonReact.createDomElement(
      tag,
      ~props={"className": classes},
      children,
    );
  },
};
