let component = ReasonReact.statelessComponent("Table");

let make =
    (
      ~tag: string="table",
      ~bordered: bool=false,
      ~striped: bool=false,
      ~inverse: bool=false,
      ~hover: bool=false,
      ~reflow: bool=false,
      ~small: bool=false,
      ~responsive: bool=false,
      ~responsiveTag: string="div",
      ~classname: option(string)=?,
      children
    ) => {
  ...component,
  render: _self => {
    let classes =
      [
        "table",
        bordered ? "table-bordered" : "",
        striped ? "table-striped" : "",
        inverse ? "table-inverse" : "",
        hover ? "table-hover" : "",
        reflow ? "table-reflow" : "",
        small ? "table-small" : "",
        Utils.unwrapStr(Utils.i, classname)
      ]
      |> String.concat(" ");
    let table =
      ReasonReact.createDomElement(
        tag,
        ~props={"className": classes},
        children
      );
    responsive ?
      ReasonReact.createDomElement(
        responsiveTag,
        ~props={"className": "table-responsive"},
        [|table|]
      ) :
      table;
  }
};
